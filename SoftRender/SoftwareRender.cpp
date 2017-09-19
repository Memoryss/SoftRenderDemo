#include "SoftwareRender.h"

namespace SoftRenderer
{

	SoftwareRender::SoftwareRender()
	{

	}

	SoftwareRender::~SoftwareRender()
	{

	}

    bool SoftwareRender::InitScene()
    {
        bool success = true;
        success = m_object.Load("models\\", "thor.obj");
        if (!success)
        {
            return false;
        }

        m_light.m_position = m_camera.m_position;
        m_light.m_ambient = vec3(0.5f);
        m_light.m_diffuse = vec3(0.5f);
        m_light.m_constAttention = 1.f;
        m_light.m_linearAttention = 0.f;
        m_light.m_quadraticAttention = 0.f;

        return true;
    }

    void SoftwareRender::Clear()
    {
        if (NULL != m_colorBuffer)
        {
            memset(m_colorBuffer, 0, m_colorBufferWidth * m_colorBufferHeight * 3);
        }

        if (NULL != m_depthBuffer)
        {
            memset(m_depthBuffer, 0, m_depthBufferWidth * m_depthBufferHeight * 2);
        }
    }

    void SoftwareRender::SetMVPMatrix(mat4x4 matrix)
    {
        m_mvpMatrix = matrix;
    }

    void SoftwareRender::SetLight(const Light &light)
    {
        m_light = light;
    }

    void SoftwareRender::DrawTriangles(Vertex *vertices, int index, int count)
    {
        if (NULL == m_colorBuffer || NULL == m_depthBuffer || NULL == vertices || index < 0 || count < 3)
        {
            return;
        }

        int startIndex = index;
        int endIndex = index + count / 3 * 3;
        
        float *mvpMatrixPtr = &m_mvpMatrix;

        //图元装配 将顶点组装为三角形
        Triangle triangle;

        for (int i = startIndex; i < endIndex; i += 3)
        {
            Vertex *vertex = m_vertices + i;
            for (int j = 0; j < 3; ++j)
            {
                auto &position = triangle.m_positions[i];
                auto &color = triangle.m_colors[i];
                auto &texcoord = triangle.m_texcoord[i];
                    //顶点变化 分开运算减少不必要的计算
                position.x = mvpMatrixPtr[0] * vertex[i].m_position.x + mvpMatrixPtr[4] * vertex[i].m_position.y + mvpMatrixPtr[8] * vertex[i].m_position.z + mvpMatrixPtr[12];
                position.y = mvpMatrixPtr[1] * vertex[i].m_position.x + mvpMatrixPtr[5] * vertex[i].m_position.y + mvpMatrixPtr[9] * vertex[i].m_position.z + mvpMatrixPtr[13];
                position.x = mvpMatrixPtr[2] * vertex[i].m_position.x + mvpMatrixPtr[6] * vertex[i].m_position.y + mvpMatrixPtr[10] * vertex[i].m_position.z + mvpMatrixPtr[14];
                position.x = mvpMatrixPtr[3] * vertex[i].m_position.x + mvpMatrixPtr[7] * vertex[i].m_position.y + mvpMatrixPtr[11] * vertex[i].m_position.z + mvpMatrixPtr[15];

                color.r = vertex[i].m_color.r;
                color.g = vertex[i].m_color.g;
                color.b = vertex[i].m_color.b;

                texcoord.s = vertex[i].m_texcoord.s;
                texcoord.t = vertex[i].m_texcoord.t;

                //光照计算
                if (NULL != m_light)
                {
                    vec3 lightDir;
                    lightDir.x = m_light->m_position.x - vertex[i].m_position.x;
                    lightDir.y = m_light->m_position.y - vertex[i].m_position.y;
                    lightDir.z = m_light->m_position.z - vertex[i].m_position.z;

                    float lightDis2 = lightDir.x * lightDir.x + lightDir.y * lightDir.y + lightDir.z * lightDir.z;
                    float lightDis = sqrt(lightDis2);

                    //漫反射角余弦值
                    float normalDotLightDir = (lightDir.x * vertex->m_normal.x + lightDir.y * vertex->m_normal.y + lightDir.z * vertex->m_normal.z) / (lightDis * 1);

                    if (normalDotLightDir < 0.f)
                    {
                        normalDotLightDir = 0.f;
                    }

                    //计算衰减参数
                    float lightAttenuation = 1.f / (m_light->m_constAttention + m_light->m_linearAttention * lightDis + m_light->m_quadraticAttention * lightDis * lightDis);

                    color.r *= (m_light->m_ambient.r + m_light->m_diffuse.r * normalDotLightDir) * lightAttenuation;
                    color.g *= (m_light->m_ambient.g + m_light->m_diffuse.g * normalDotLightDir) * lightAttenuation;
                    color.b *= (m_light->m_ambient.b + m_light->m_diffuse.b * normalDotLightDir) * lightAttenuation;
                }
            }

            //裁剪三角形

        }
    }

    void SoftwareRender::ClipTriangle(Triangle &triangle)
    {

    }

    void SoftwareRender::Render(float frameTime)
    {
        //清楚深度缓存和颜色缓存
        Clear();

        //设置矩阵
        SetMVPMatrix(m_camera.m_viewPorjectMatrix);

    }

}