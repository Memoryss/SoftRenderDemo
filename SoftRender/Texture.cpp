#include "Texture.h"

#include <string>
#include <assert.h>
#include "FreeImage.h"
#include "log.h"
#include "ResourceManager.h"

namespace SoftRenderer {

	const float CD_255 = 1.0f / 255;
	const float CD_65535 = 1.0f / 65535;

    Texture::Texture()
    {
        
    }

    Texture::~Texture()
    {

    }

    bool Texture::LoadTexture(const char *textureFileName)
    {
		std::string errorText = "Error: load file ";
		errorText.append(textureFileName);
		errorText.append("->");

        std::string path = ResourceManager::Instance()->GetFilePath(textureFileName);
        if (path.empty())
        {
            SLOG(errorText + " not exist");
            return false;
        }

        FREE_IMAGE_FORMAT image_format = FreeImage_GetFileType(path.c_str());
        if (FIF_UNKNOWN == image_format)
        {
            image_format = FreeImage_GetFIFFromFilename(path.c_str());
        }

        if (FIF_UNKNOWN == image_format)
        {
			SLOG(errorText + "FIF  is FIF_UNKNOWN");
            return false;
        }

		FIBITMAP *dib = NULL;
		if (FreeImage_FIFSupportsReading(image_format))
		{
			dib = FreeImage_Load(image_format, path.c_str());
		}

		if (NULL == dib)
		{
			SLOG(errorText + "dib is null");
			return false;
		}

		int width = FreeImage_GetWidth(dib);
		int height = FreeImage_GetHeight(dib);
		int pitch = FreeImage_GetPitch(dib);
		int bpp = FreeImage_GetBPP(dib);	//返回每个像素的大小

		if (0 == width || 0 == height)
		{
			SLOG(errorText + "width or height is 0");
			FreeImage_Unload(dib);
			return false;
		}

        bpp /= 8;
        if (bpp != 3 && bpp != 4)
        {
            SLOG(errorText + "bpp is not 24 or 32");
            FreeImage_Unload(dib);
            return false;
        }

		BYTE *bits = FreeImage_GetBits(dib);
		if (NULL == bits)
		{
			SLOG(errorText + "bits is null");
			FreeImage_Unload(dib);
			return false;
		}

        TextureFormat format = bpp == 3 ? R8G8B8 : R8G8B8A8;
		CreateTexture(width, height, format);
		BYTE *pixel = (BYTE*)this->m_data;

		//填充数据
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < height; ++x)
			{
				for (int i = 0; i < bpp; ++i)
				{
					pixel[(width * y + x) * bpp + i] = bits[pitch * y + bpp * x + i];
				}
			}
		}
		FreeImage_Unload(dib);

        return true;
    }

    /*
    void Texture::getColorNearest(int x, int y, vec4 &color)
    {
		if (NULL != m_data)
		{
            BYTE *b;
			switch (m_format)
			{
			case SoftRenderer::TF_NONE:
				break;
			case SoftRenderer::TF_BGR24:
				b = (BYTE *)m_data + y * m_pitch + x * 3;
				
				color.b = *b * CD_255;
				++b;
				color.g = *b * CD_255;
				++b;
				color.r = *b * CD_255;
				break;
			case SoftRenderer::TF_DEPTH16:
				b = (BYTE *)m_data + y * m_pitch + x * 2;
				color.b = color.g = color.r = *b * CD_65535;
				break;
			default:
                color.b = color.g = color.r = 0.f;
                color.a = 1.f;
				break;
			}
		}
		else
		{
            color.b = color.g = color.r = 0.f;
            color.a = 1.f;
		}
    }

    void Texture::getColorBilinear(float s, float t, vec4 &color)
    {
		if (NULL != m_data)
		{
            s -= (int)s;
            t -= (int)t;

            if (s < 0.0f) s += 1.0f;
            if (t < 0.0f) t += 1.0f;

            float fx = s * m_width - 0.5f, fy = t * m_height - 0.5f;

            if (fx < 0.0f) fx += m_width;
            if (fy < 0.0f) fy += m_height;

			//取出像素上的四个点
			int x1 = fx;
			int x2 = (x1 + 1) % m_width; //超过则移到开始位置
			int y1 = fy;
			int y2 = (y1 + 1) % m_height;

			switch (m_format)
			{
			case SoftRenderer::TF_NONE:
				break;
			case SoftRenderer::TF_BGR24:
            {
                BYTE *line1 = (BYTE *)m_data + m_pitch * y1;
                BYTE *line2 = (BYTE *)m_data + m_pitch * y2;

                int deltaX1 = x1 * 3;
                int deltaX2 = x2 * 3;

                BYTE *pixel1 = line1 + deltaX1;
                BYTE *pixel2 = line1 + deltaX2;
                BYTE *pixel3 = line2 + deltaX1;
                BYTE *pixel4 = line2 + deltaX2;

                //每个像素的权重
                float u1 = fx - x1;
                float u2 = 1.f - u1;
                float v1 = fy - y1;
                float v2 = 1.f - v1;

                //为了减少计算量  在这里进行颜色映射
                u1 *= CD_255;
                u2 *= CD_255;

                float u1v1 = u1 * v1;
                float u1v2 = u1 * v2;
                float u2v1 = u2 * v1;
                float u2v2 = u2 * v2;

                //加权平均值
                color.b = *pixel1 * u1v1 + *pixel2 * u2v1 + *pixel3 * u1v2 + *pixel4 * u2v2;
                ++pixel1; ++pixel2; ++pixel3; ++pixel4;
                color.g = *pixel1 * u1v1 + *pixel2 * u2v1 + *pixel3 * u1v2 + *pixel4 * u2v2;
                ++pixel1; ++pixel2; ++pixel3; ++pixel4;
                color.r = *pixel1 * u1v1 + *pixel2 * u2v1 + *pixel3 * u1v2 + *pixel4 * u2v2;
            }
				break;
			case SoftRenderer::TF_DEPTH16:
            {
                BYTE *line1 = (BYTE *)m_data + m_pitch * y1;
                BYTE *line2 = (BYTE *)m_data + m_pitch * y2;

                int deltaX1 = x1 * 2;
                int deltaX2 = x2 * 2;

                BYTE *pixel1 = line1 + deltaX1;
                BYTE *pixel2 = line1 + deltaX2;
                BYTE *pixel3 = line2 + deltaX1;
                BYTE *pixel4 = line2 + deltaX2;

                //每个像素的权重
                float u1 = fx - x1;
                float u2 = 1.f - u1;
                float v1 = fy - y1;
                float v2 = 1.f - v1;

                //为了减少计算量  在这里进行颜色映射
                u1 *= CD_255;
                u2 *= CD_255;

                float u1v1 = u1 * v1;
                float u1v2 = u1 * v2;
                float u2v1 = u2 * v1;
                float u2v2 = u2 * v2;

                //加权平均值
                color.b = color.g = color.r = *pixel1 * u1v1 + *pixel2 * u2v1 + *pixel3 * u1v2 + *pixel4 * u2v2;
            }
				break;
			default:
                color.b = color.g = color.r = 0.f;
                color.a = 1.f;
				break;
			}
		}
		else
		{
            color.b = color.g = color.r = 0.f;
            color.a = 1.f;
		}
    }
    */

    float Texture::GetShadowNearest(vec4 &texcoord)
    {
		//TODO
        return 0.f;
    }

    float Texture::GetShadowBilinear(vec4 &texcoord)
    {
		//TODO
        return 0.f;
    }

    void Texture::Clear()
    {
        if (NULL != m_data)
        {
            BYTE *byte = (BYTE *)m_data;
            delete byte;
        }

        reset();
    }

    int Texture::GetWidth() const
    {
        return m_width;
    }

    int Texture::GetHeight() const
    {
        return m_height;
    }

    void * Texture::GetData() const
    {
        return m_data;
    }

    TextureFormat Texture::GetFormat() const
    {
        return m_format;
    }

    void Texture::reset()
    {
        m_data = NULL;

        m_width = 0;
        m_height = 0;
        m_format = UNKNOWN;
    }

    vec4 Texture::getColor(int u, int v)
    {
        assert(u >= 0 && u < m_width && v >= 0 && u < m_height);

        vec4 color(0.f, 0.f, 0.f, 1.f);
        int index = v * m_height + u;
        const BYTE *data = (const BYTE *)m_data;

        switch (m_format)
        {
        case SoftRenderer::UNKNOWN:
            break;
        case SoftRenderer::A8:
            color.r = 1.f;
            color.g = 1.f;
            color.b = 1.f;
            color.a = data[index] / 255.f;
            break;
        case SoftRenderer::R8G8B8:
            color.b = data[index * 3] / 255.f;
            color.g = data[index * 3 + 1] / 255.f;
            color.r = data[index * 3 + 2] / 255.f;
            color.a = 1.f;
            break;
        case SoftRenderer::R8G8B8A8:
            color.b = data[index * 4] / 255.f;
            color.g = data[index * 4 + 1] / 255.f;
            color.r = data[index * 4 + 2] / 255.f;
            color.a = data[index * 4 + 3] / 255.f;
            break;
        default:
            break;
        }

        return color;
    }

    void Texture::CreateTexture(int width, int height, TextureFormat format)
	{
		//先清除之前的纹理
		reset();

		if (width > 0 && height > 0)
		{
			switch (format)
			{
			case A8:
				m_data = new BYTE[width * height];
				break;
			case D16:
				m_data = new BYTE[width * height * 2];
				break;
            case R8G8B8A8:
                m_data = new BYTE[width * height * 4];
                break;
            case R8G8B8:
                m_data = new BYTE[width * height * 3];
			default:
				break;
			}

			m_width = width;
			m_height = width;
			m_format = format;
		}
	}

    void Texture::Sample2D(float x, float y, const SamplerState &state, vec4 &color)
    {
        if (NULL == m_data)
        {
            color = vec4(0.f, 0.f, 0.f, 1.f);
            return;
        }

        switch (state.m_wrapMode)
        {
        case BORAD:
            if (x < 0 || x > 1.f || y < 0 || y > 1.f)
            {
                color = state.m_boardColor;
            }
            break;
        case CLAMP:
            if (x < 0)
            {
                x = 0;
            }

            if ( x > 1.f)
            {
                x = 1.f;
            }

            if (y < 0)
            {
                y = 0.f;
            }

            if (y > 1.f)
            {
                y = 1.f;
            }
            break;
        case WRAP:
            while (x < 0)
            {
                x += 1;
            }
            while (x > 1.f)
            {
                x -= 1.f;
            }
            while (y < 0)
            {
                y = 0.f;
            }
            while (y > 1.f)
            {
                y -= 1.f;
            }
            break;
        default:
            break;
        }

        float fu = x * (m_width - 1);
        float fv = y * (m_height - 1);
        int u = (int)fu;
        int v = (int)fv;

        switch (state.m_filter)
        {
        case NEAREST:
            color = getColor(u, v);
            break;
        case LINEAR:
        {
            int u1 = u + 1 > m_width ? u + 1 : u;
            int v1 = v + 1 > m_height ? v + 1 : v;
            vec4 color1, color2, color3, color4;
            color1 = getColor(u, v);
            color2 = getColor(u1, v);
            color3 = getColor(u, v1);
            color4 = getColor(u1, v1);

            float du = fu - u;
            float dv = fv - v;

            vec4 color5 = color1 + (color2 - color1) * du;
            vec4 color6 = color3 + (color4 - color3) * du;

            color = color5 + (color6 - color5) * dv;
        }
            break;
        default:
            color = vec4(0.f, 0.f, 0.f, 1.f);
            break;
        }
    }

}
