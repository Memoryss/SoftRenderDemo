#include "SoftwareRender.h"

#include <assert.h>
#include <algorithm>
#include "Texture.h"
#include "Light.h"
#include "RenderBuffer.h"
#include "Camera.h"
#include "Shader.h"

namespace SoftRenderer
{

    SoftwareRender::SoftwareRender(HWND hwnd, int w, int h)
    {
        m_context = new SoftwareRenderContext(hwnd, w, h);

        m_width = w;
        m_height = h;

        m_colorBuffer = new vec3[m_width * m_height];
        m_depthBuffer = new float[m_width * m_height];
    }

    SoftwareRender::~SoftwareRender()
    {
        if (NULL != m_colorBuffer)
        {
            delete[] m_colorBuffer;
        }

        if (NULL != m_depthBuffer)
        {
            delete[] m_depthBuffer;
        }

        //TODO light texture camera
    }

    void SoftwareRender::Resize(int width, int height)
    {
        assert(width > 1 && height > 1);
        m_context->Resize(width, height);

        if (NULL != m_colorBuffer)
        {
            delete[] m_colorBuffer;
        }

        if (NULL != m_depthBuffer)
        {
            delete[] m_depthBuffer;
        }

        m_width = width;
        m_height = height;

        m_colorBuffer = new vec3[m_width * m_height];
        m_depthBuffer = new float[m_width * m_height];
    }

    void SoftwareRender::Clear(const vec3 &color /*= vec3(0.f, 0.f, 0.f)*/, float depth /*= 1.f*/)
    {
        if (color == 0.f)
        {
            memset(m_colorBuffer, 0, m_width * m_height * 12);
        }
        else
        {
            for (int i = 0; i < m_width * m_height; ++i)
            {
                m_colorBuffer[i] = color;
            }
        }

        for (int i = 0; i < m_width * m_height; ++i)
        {
            m_depthBuffer[i] = depth;
        }
    }

    void SoftwareRender::SetWorldMatrix(const mat4x4 &m)
    {
        m_worldMatrix = m;
    }

    void SoftwareRender::SetViewMatrix(const mat4x4 &m)
    {
        m_viewMatrix = m;
    }

    void SoftwareRender::SetProjMatrix(const mat4x4 &m)
    {
        m_projMatrix = m;
    }

    void SoftwareRender::SetCamera(Camera *cam)
    {
        m_camera = cam;
    }

    void SoftwareRender::SetLight(Light *light)
    {
        m_light = light;
    }

    void SoftwareRender::SetTexture(Texture *texture)
    {
        m_texture = texture;
    }

    void SoftwareRender::SetShader(Shader *shader)
    {
        m_shader = shader;
    }

    void SoftwareRender::SetRenderState(const SoftwareRenderState &state)
    {
        m_renderState = state;
    }

    void SoftwareRender::Render(RenderBuffer *buffer)
    {
        if (buffer->vbuffer.size() <= 0 || buffer->primCount <= 0)
        {
            return;
        }

        //顶点处理
        m_rasterVertexBuffer.resize(buffer->vbuffer.size());
        //TODO 优化 需要每个顶点就需要？
        for (int i = 0; i < buffer->vbuffer.size(); ++i)
        {
            vertexShader(&m_rasterVertexBuffer[i], &buffer->vbuffer[i]);
        }

        //图元
        RasterizerVertex a, b, c;
        for (int i = 0; i < buffer->primCount; ++i)
        {
            if (buffer->primType == PT_TriangleList)
            {
                //索引列表
                if (buffer->ibuffer.size() > 0)
                {
                    a = m_rasterVertexBuffer[buffer->ibuffer[i * 3 + 0]];
                    b = m_rasterVertexBuffer[buffer->ibuffer[i * 3 + 1]];
                    c = m_rasterVertexBuffer[buffer->ibuffer[i * 3 + 2]];
                }
                else
                {
                    a = m_rasterVertexBuffer[i * 3 + 0];
                    b = m_rasterVertexBuffer[i * 3 + 1];
                    c = m_rasterVertexBuffer[i * 3 + 2];
                }

                //背面剔除
                if (cullBackFace(&a, &b, &c))
                {
                    continue;
                }

                //视口变化：透视除法，屏幕映射
                a.position.x /= a.position.w;
                a.position.y /= a.position.w;
                b.position.x /= b.position.w;
                b.position.y /= b.position.w;
                c.position.x /= c.position.w;
                c.position.y /= c.position.w;

                //透视除法之后 点在cvv中 范围为-1 ~ 1 注意屏幕坐标和y坐标相反
                a.position.x = (a.position.x + 1) / 2 * m_width;
                a.position.y = (1 - a.position.y) / 2 * m_width;
                b.position.x = (b.position.x + 1) / 2 * m_width;
                b.position.y = (1 - b.position.y) / 2 * m_width;
                c.position.x = (c.position.x + 1) / 2 * m_width;
                c.position.y = (1 - c.position.y) / 2 * m_width;

                //光栅化
                rasterizeTriangle(&a, &b, &c);
            }
        }
    }

    void SoftwareRender::Begin()
    {
        m_texture = NULL;
        m_light = NULL;
        m_shader = NULL;
    }

    void SoftwareRender::End()
    {
        
    }

    void SoftwareRender::Present()
    {
        m_context->Present(m_colorBuffer);
    }

    void SoftwareRender::rasterizePoint(const RasterizerVertex *point)
    {
		RasterizerVertex v = *point;

		int x = (int)v.position.x;
		int y = (int)v.position.y;
		if (x >= 0 && x < m_width && y >= 0 && y < m_height)
		{
			if (fragmentShader(&v))
			{
				output(x, y, &v);
			}
		}
    }

    void SoftwareRender::rasterizeLine(const RasterizerVertex *pointA, const RasterizerVertex *pointB)
    {
		if (pointA->position.x > pointB->position.x)
		{
			std::swap(pointA, pointB);
		}

		RasterizerVertex v;

		vec2i a(pointA->position.x, pointA->position.y);
		vec2i b(pointB->position.y, pointB->position.y);	
		vec2i ab = b - a;

		//斜率小于0.5
		if (ab.x > std::abs(ab.y))
		{
			//计算斜率
			float k = (float)ab.y / ab.x;
			int x = a.x;
			int y = a.y;

			if (k > 0)
			{
				//四舍五入 > 0.5 y+1
				float e = -0.5f;

				for (int i = 0; i < ab.x; ++i)
				{
					x = x + 1;
					e = e + k;
					if (e > 0)
					{
						y += 1;
						e -= 1.f;
					}

					if (x >= 0 && x < m_width && y >= 0 && y <= m_height)
					{
						float ratio_x = ab.x > 0 ? (float)i / ab.x : 1;
						RasterizerVertex::Lerp(v, *pointA, *pointB, ratio_x);
						if (fragmentShader(&v))
						{
							output(x, y, &v);
						}
					}
				}
			}
			else if (k == 0)
			{
				for (int i = 0; i < ab.x; ++i)
				{
					x = x + 1;
					if (x >= 0 && x < m_width && y >= 0 && y <= m_height)
					{
						float ratio_x = ab.x > 0 ? (float)i / ab.x : 1;
						RasterizerVertex::Lerp(v, *pointA, *pointB, ratio_x);
						if (fragmentShader(&v))
						{
							output(x, y, &v);
						}
					}
				}
			}
			else
			{
				float e = -0.5f;
				for (int i = 0; i < ab.x; ++i)
				{
					x = x + 1;
					//k < 0
					e = e - k;
					if (e > 0)
					{
						y = y - 1;
						e = e - 1.f;
					}

					if (x >= 0 && x < m_width && y >= 0 && y <= m_height)
					{
						float ratio_x = ab.x > 0 ? (float)i / ab.x : 1;

						RasterizerVertex::Lerp(v, *pointA, *pointB, ratio_x);
						if (fragmentShader(&v))
						{
							output(x, y, &v);
						}
					}
				}
			}
		}
		//斜率>0.5
		else
		{
			float k = (float)ab.x / ab.y;
			int x = a.x;
			int y = a.y;

			if (k > 0)
			{
				float e = -0.5f;

				for (int i = 0; i < ab.y; ++i)
				{
					y += 1;
					e += k;
					if (e > 0.f)
					{
						x += 1;
						e -= 1.f;
					}

					if (y >= 0 && y <= m_height && x >= 0 && x < m_width)
					{
						float ratio_y = ab.y > 0 ? (float)i / ab.y : 1;
						RasterizerVertex::Lerp(v, *pointA, *pointB, ratio_y);
						if (fragmentShader(&v))
						{
							output(x, y, &v);
						}
					}
				}
			}
			else if (k == 0)
			{
				if (ab.y > 0)
				{
					for (int i = 0; i < ab.y; ++i)
					{
						y = y + 1;
						if (x >= 0 && x < m_width && y >= 0 && y <= m_height)
						{
							float ratio_y = ab.y > 0 ? (float)i / ab.y : 1;
							RasterizerVertex::Lerp(v, *pointA, *pointB, ratio_y);
							if (fragmentShader(&v))
							{
								output(x, y, &v);
							}
						}
					}
				}
				else
				{
					for (int i = 0; i < -ab.y; ++i)
					{
						y -= 1;
						if (x >= 0 && x < m_width && y >= 0 && y <= m_height)
						{
							float ratio_y = -ab.y > 0 ? (float)i / -ab.y : 1;
							RasterizerVertex::Lerp(v, *pointA, *pointB, ratio_y);
							if (fragmentShader(&v))
							{
								output(x, y, &v);
							}
						}
					}
				}
			}
			else
			{
				float e = -0.5f;

				for (int i = 0; i < -ab.y; ++i)
				{
					y -= 1;
					e -= k;
					if (e > 0.f)
					{
						x += 1;
						e -= 1.f;
					}

					if (x >= 0 && x < m_width && y >= 0 && y <= m_height)
					{
						float ratio_y = -ab.y > 0 ? (float)i / -ab.y : 1;
						RasterizerVertex::Lerp(v, *pointA, *pointB, ratio_y);
						if (fragmentShader(&v))
						{
							output(x, y, &v);
						}
					}
				}
			}
		}
    }

    void SoftwareRender::rasterizeTriangle(const RasterizerVertex *pointA, const RasterizerVertex *pointB, const RasterizerVertex *pointC)
    {
        //确保pointA是最上面的点
        if (pointA->position.y > pointB->position.y)
        {
            std::swap(pointA, pointB);
        }
        if (pointA->position.y > pointC->position.y)
        {
            std::swap(pointA, pointC);
        }

        //pointB在pointC的左边
        if (pointB->position.x > pointC->position.x)
        {
            std::swap(pointB, pointC);
        }

        vec2i a(pointA->position.x, pointA->position.y);
        vec2i b(pointB->position.x, pointB->position.y);
        vec2i c(pointC->position.x, pointC->position.y);
        vec2i ab = b - a;
        vec2i ac = c - a;

        RasterizerVertex v1, v2, v;
        if (b.y > c.y)
        {
            //三角形类别
            /**
                A
                    C
            B
            */

            //画上半部分
            int start_y = a.y, end_y = c.y;
            start_y = std::max(start_y, 0);
            end_y = std::min(end_y, m_height);

            while (start_y < end_y)
            {
                //y轴比率
                float ratio_ab = ab.y > 0 ? (float)(start_y - a.y) / ab.y : 1;
                float ratio_ac = ac.y > 0 ? (float)(start_y - a.y) / ac.y : 1;

                int x1 = (int)(a.x + ab.x * ratio_ab);
                int x2 = (int)(a.x + ac.x * ratio_ac);

                //获取三角形边上的点
                RasterizerVertex::Lerp(v1, *pointA, *pointB, ratio_ab);
                RasterizerVertex::Lerp(v2, *pointA, *pointC, ratio_ac);

                //交换下位置 便于理解和计算
                if (x1 > x2)
                {
                    std::swap(x1, x2);
                    std::swap(v1, v2);
                }

                int start_x = std::max(x1, 0);
                int end_x = std::max(x2, m_width);

                for (int x = start_x; x < end_x; ++x)
                {
                    //x轴比率
                    float ratio_x1x2 = (x2 - x1) > 0 ? (float)(x - x1) / (x2 - x1) : 1;

                    RasterizerVertex::Lerp(v, v1, v2, ratio_x1x2);
                    //像素着色
                    if (fragmentShader(&v))
                    {
                        //输出到colorbuff
                        output(x, start_y, &v);
                    }
                }
                ++start_y;
            }

            //画下半部分
            vec2i cb(b.x - c.x, b.y - c.y);
            end_y = std::min(b.y, m_height);

            while (start_y < end_y)
            {
                float ratio_ab = ab.y > 0 ? (float)(start_y - a.y) / ab.y : 1;
                float ratio_cb = cb.y > 0 ? (float)(start_y - c.y) / cb.y : 1;

                int x1 = (int)(a.x + ab.x * ratio_ab);
                int x2 = (int)(a.x + ac.x * ratio_cb);

                RasterizerVertex::Lerp(v1, *pointA, *pointB, ratio_ab);
                RasterizerVertex::Lerp(v2, *pointC, *pointB, ratio_cb);

                if (x1 > x2)
                {
                    std::swap(x1, x2);
                }

                int start_x = std::max(x1, 0);
                int end_x = std::min(x2, m_width);

                for (int x = start_x; x < end_x; ++x)
                {
                    float ratio_x1x2 = (x2 - x1) > 0 ? (float)(x - x1) / (x2 - x1) : 1;
                    RasterizerVertex::Lerp(v, v1, v2, ratio_x1x2);
                    if (fragmentShader(&v))
                    {
                        output(x, start_y, &v);
                    }
                }
                ++start_y;
            }
        }
        else
        {
            //三角形类别
            /**
                A
            B
                    C
            */

            //画上半部分
			int start_y = a.y, end_y = b.y;
			start_y = std::max(0, start_y);
			end_y = std::min(m_height, end_y);
			
			while (start_y < end_y)
			{
				//x轴比率
				float ratio_ab = ab.y > 0 ? (float)(start_y - a.y) / ab.y : 1;
				float ratio_ac = ac.y > 0 ? (float)(start_y - a.y) / ac.y : 1;

				int x1 = (int)(a.x + ratio_ab * ab.x);
				int x2 = (int)(a.x + ratio_ab * ac.x);

				RasterizerVertex::Lerp(v1, *pointA, *pointB, ratio_ab);
				RasterizerVertex::Lerp(v2, *pointA, *pointC, ratio_ac);

				if (x1 > x2)
				{
					std::swap(x1, x2);
					std::swap(v1, v2);
				}

				int start_x = std::max(0, x1);
				int end_x = std::min(m_width, x2);
				for (int x = x1; x < x2; ++x)
				{
					float ratio_x1x2 = (x2 - x1) > 0 ? (float)(x - x1) / (x2 - x1) : 1;
					RasterizerVertex::Lerp(v, v1, v2, ratio_x1x2);
					if (fragmentShader(&v))
					{
						output(x, start_y, &v);
					}
				}
				++start_y;
			}

			//画下半部分
			vec2i bc(c.x - b.x, c.y - b.y);
			end_y = std::min(m_height, c.y);
			while (start_y < end_y)
			{
				float ratio_bc = bc.y > 0 ? (float)(start_y - b.y) / bc.y : 1;
				float ratio_ac = ac.y > 0 ? (float)(start_y - a.y) / ac.y : 1;

				int x1 = (int)(b.x + bc.x * ratio_bc);
				int x2 = (int)(a.x + ac.x * ratio_ac);

				RasterizerVertex::Lerp(v1, *pointB, *pointC, ratio_bc);
				RasterizerVertex::Lerp(v2, *pointA, *pointC, ratio_ac);

				if (x1 > x2)
				{
					std::swap(x1, x2);
					std::swap(v1, v2);
				}

				int start_x = std::max(x1, 0);
				int end_x = std::min(x2, m_height);
				for (int x = start_x; x < end_x; ++x)
				{
					int ratio_x1x2 = (x2 - x1) > 0 ? (float)(x - x1) / (x2 - x1) : 1;

					RasterizerVertex::Lerp(v, v1, v2, ratio_x1x2);
					if (fragmentShader(&v))
					{
						output(x, start_y, &v);
					}
				}
				++start_y;
			}
        }
    }

    bool SoftwareRender::cullBackFace(const RasterizerVertex *pa, const RasterizerVertex *pb, const RasterizerVertex *pc)
    {
        if (m_renderState.GetCullFaceType() == CFT_None)
        {
            return false;
        }

        //xy二维可以判断背面
        vec2 ab, ac;
        ab.x = pb->position.x - pa->position.x;
        ab.y = pb->position.y - pa->position.y;

        ac.x = pc->position.x - pa->position.x;
        ac.y = pc->position.y - pa->position.y;

        float cross = ab.x * ac.y - ab.y * ac.x;

        //剔除背面  法线朝向z正方向的被剔除
        if (m_renderState.GetCullFaceType() == CFT_BACK)
        {
            return cross > 0.f;
        }
        else
        {
            return cross < 0.f;
        }
    }

    void SoftwareRender::vertexShader(RasterizerVertex *v_out, const Vertex *v_in)
    {
        m_shader->VertexShader(v_out, v_in);
    }

    bool SoftwareRender::fragmentShader(RasterizerVertex *v)
    {
        return m_shader->FragmentShader(v);
    }

    void SoftwareRender::output(int x, int y, const RasterizerVertex *v)
    {
        int index = y * m_width + x;
        //z也进行透视除法
        float depth = v->position.z / v->position.w;

        //深度测试 TODO 拿到最前面 减少性能损耗？
        if (!depthTest(m_depthBuffer[index], depth))
        {
            return;
        }

        if (m_renderState.IsDepthMask())
        {
            m_depthBuffer[index] = depth;
        }

        vec3 *fragmentColor = m_colorBuffer + index;
        switch (m_renderState.GetBlendType())
        {
        case BT_Opacity:
            fragmentColor->r = v->color.r;
            fragmentColor->g = v->color.g;
            fragmentColor->b = v->color.b;
            break;
        case BT_Add:
            fragmentColor->r += v->color.r;
            fragmentColor->g += v->color.g;
            fragmentColor->b += v->color.b;
            break;
        case BT_AlphaBlend:
            fragmentColor->r = v->color.a * v->color.r + (1 - v->color.a) * fragmentColor->r;
            fragmentColor->g = v->color.a * v->color.g + (1 - v->color.a) * fragmentColor->g;
            fragmentColor->b = v->color.a * v->color.b + (1 - v->color.a) * fragmentColor->b;
            break;
        default:
            break;
        }

        std::clamp(fragmentColor->r, 0.f, 1.f);
        std::clamp(fragmentColor->g, 0.f, 1.f);
        std::clamp(fragmentColor->b, 0.f, 1.f);
    }

    bool SoftwareRender::depthTest(float oldDepth, float newDepth)
    {
        switch (m_renderState.GetDepthTestType())
        {
        case DTT_Always:
            return true;
        case DTT_Less:
            return newDepth < oldDepth;
        case DTT_LessEqual:
            return newDepth <= oldDepth;
        case DTT_Greater:
            return newDepth > oldDepth;
        case DTT_GreaterEqual:
            return newDepth >= oldDepth;
        case DTT_Equal:
            return newDepth == oldDepth;
        case DTT_NotEqual:
            return newDepth != oldDepth;
        default:
            break;
        }

        return false;
    }

}