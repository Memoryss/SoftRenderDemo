#include "Texture.h"

#include <string>
#include "FreeImage.h"
#include "log.h"

namespace SoftRenderer {

	const int CD_255 = 1.0f / 255;
	const int CD_65535 = 1.0f / 65535;

    Texture::Texture()
    {
        init();
    }

    Texture::~Texture()
    {

    }

    bool Texture::LoadTexture(const char *textureFileName)
    {
		std::string errorText = "Error: load file ";
		errorText.append(textureFileName);
		errorText.append("->");

        FREE_IMAGE_FORMAT image_format = FreeImage_GetFileType(textureFileName);
        if (FIF_UNKNOWN == image_format)
        {
            image_format = FreeImage_GetFIFFromFilename(textureFileName);
        }

        if (FIF_UNKNOWN == image_format)
        {
			SLOG(errorText + "FIF  is FIF_UNKNOWN");
            return false;
        }

		FIBITMAP *dib = NULL;
		if (FreeImage_FIFSupportsReading(image_format))
		{
			dib = FreeImage_Load(image_format, textureFileName);
		}

		if (NULL == dib)
		{
			SLOG(errorText + "dib is null");
			return false;
		}

		int width = FreeImage_GetWidth(dib);
		int height = FreeImage_GetHeight(dib);
		int pitch = FreeImage_GetPitch(dib);
		int bpp = FreeImage_GetBPP(dib);	//����ÿ�����صĴ�С

		if (0 == width || 0 == height)
		{
			SLOG(errorText + "width or height is 0");
			FreeImage_Unload(dib);
			return false;
		}

		if (PS_24 != bpp || PS_32 != bpp)
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

		CreateTexture(width, height, TF_BGR24);
		BYTE *pixel = (BYTE*)this->m_data;

		bpp /= 8;
		//�������
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < height; ++x)
			{
				for (int i = 0; i < 3; ++i)
				{
					pixel[(width * y + x) * 3 + i] = bits[pitch * y + bpp * x + i];
				}
			}
		}
		FreeImage_Unload(dib);
    }

    void Texture::GetColorNearest(float s, float t, vec3 &color)
    {
		if (NULL != m_data)
		{
			//����Ϊ0-1
			s -= (int)s;
			t -= (int)t;
			if (s < 0.0f)
			{
				s = 1.0f;
			}
			if (t < 0.f)
			{
				t = 1.0f;
			}

			int x = (int)(m_width * s);
			int y = (int)(m_height * t);

			switch (m_format)
			{
			case SoftRenderer::TF_NONE:
				break;
			case SoftRenderer::TF_BGR24:
				BYTE *b = (BYTE *)m_data + y * m_pitch + x * 3;
				
				color.b = *b * CD_255;
				++b;
				color.g = *b * CD_255;
				++b;
				color.r = *b * CD_255;
				break;
			case SoftRenderer::TF_DEPTH16:
				BYTE *b = (BYTE *)m_data + y * m_pitch + x * 2;
				color.b = color.g = color.r = *b * CD_65535;
				break;
			default:
				break;
			}
		}
		else
		{
			color.b = color.g = color.r = 1.f;
		}
    }

    void Texture::GetColorBilinear(float s, float t, vec3 &color)
    {
		if (NULL != m_data)
		{
			//����Ϊ0-1
			s -= (int)s;
			t -= (int)t;
			if (s < 0.0f)
			{
				s = 1.0f;
			}
			if (t < 0.f)
			{
				t = 1.0f;
			}

			float fx = s * m_width - 0.5f;
			float fy = t * m_height - 0.5f;

			//���<0 �Ƶ�ͼ��ĩβ
			if (fx < 0.0f)
			{
				fx += m_width;
			}
			if (fy < 0.0f)
			{
				fy += m_height;
			}

			//ȡ�������ϵ��ĸ���
			int x1 = (int)fx;
			int x2 = (x1 + 1) % m_width; //�������ƶ���ʼλ��
			int y1 = (int)fx;
			int y2 = (y1 + 1) % m_height;

			switch (m_format)
			{
			case SoftRenderer::TF_NONE:
				break;
			case SoftRenderer::TF_BGR24:
				BYTE *line1 = (BYTE *)m_data + m_pitch * y1;
				BYTE *line2 = (BYTE *)m_data + m_pitch * y2;

				int deltaX1 = x1 * 3;
				int deltaX2 = x2 * 3;

				BYTE *pixel1 = line1 + deltaX1;
				BYTE *pixel2 = line1 + deltaX2;
				BYTE *pixel3 = line2 + deltaX1;
				BYTE *pixel4 = line2 + deltaX2;

				//ÿ�����ص�Ȩ��
				float u1 = fx - x1;
				float u2 = 1.f - u1;
				float v1 = fy - y1;
				float v2 = 1.f - v1;

				//Ϊ�˼��ټ�����  �����������ɫӳ��
				u1 *= CD_255;
				u2 *= CD_255;

				float u1v1 = u1 * v1;
				float u1v2 = u1 * v2;
				float u2v1 = u2 * v1;
				float u2v2 = u2 * v2;

				//��Ȩƽ��ֵ
				color.b = *pixel1 * u1v1 + *pixel2 * u2v1 + *pixel3 * u1v2 + *pixel4 * u2v2;
				++pixel1; ++pixel2; ++pixel3; ++pixel4;
				color.g = *pixel1 * u1v1 + *pixel2 * u2v1 + *pixel3 * u1v2 + *pixel4 * u2v2;
				++pixel1; ++pixel2; ++pixel3; ++pixel4;
				color.r = *pixel1 * u1v1 + *pixel2 * u2v1 + *pixel3 * u1v2 + *pixel4 * u2v2;

				break;
			case SoftRenderer::TF_DEPTH16:
				BYTE *line1 = (BYTE *)m_data + m_pitch * y1;
				BYTE *line2 = (BYTE *)m_data + m_pitch * y2;

				int deltaX1 = x1 * 2;
				int deltaX2 = x2 * 2;

				BYTE *pixel1 = line1 + deltaX1;
				BYTE *pixel2 = line1 + deltaX2;
				BYTE *pixel3 = line2 + deltaX1;
				BYTE *pixel4 = line2 + deltaX2;

				//ÿ�����ص�Ȩ��
				float u1 = fx - x1;
				float u2 = 1.f - u1;
				float v1 = fy - y1;
				float v2 = 1.f - v1;

				//Ϊ�˼��ټ�����  �����������ɫӳ��
				u1 *= CD_255;
				u2 *= CD_255;

				float u1v1 = u1 * v1;
				float u1v2 = u1 * v2;
				float u2v1 = u2 * v1;
				float u2v2 = u2 * v2;

				//��Ȩƽ��ֵ
				color.b = color.g = color.r = *pixel1 * u1v1 + *pixel2 * u2v1 + *pixel3 * u1v2 + *pixel4 * u2v2;
				break;
			default:
				break;
			}
		}
		else
		{
			color.b = color.g = color.r = 1.f;
		}
    }

    float Texture::GetShadowNearest(vec4 &texcoord)
    {
		//TODO
    }

    float Texture::GetShadowBilinear(vec4 &texcoord)
    {
		//TODO
    }

    void Texture::Clear()
    {
        if (NULL != m_data)
        {
            switch (m_format)
            {
            case TextureFormat::TF_DEPTH16:
                delete[](unsigned char *)m_data;
                break;
            case TextureFormat::TF_BGR24:
                delete[](unsigned short*)m_data;
                break;
            default:
                break;
            }
        }

        init();
    }

    int Texture::GetWidth() const
    {
        return m_width;
    }

    int Texture::GetHeight() const
    {
        return m_height
    }

    void * Texture::GetData() const
    {
        return m_data;
    }

    TextureFormat Texture::GetFormat() const
    {
        return m_format;
    }

    void Texture::init()
    {
        m_data = NULL;

        m_width = 0;
        m_height = 0;
        m_format = TextureFormat::TF_NONE;
        m_pitch = 0;
    }

	void Texture::CreateTexture(int width, int height, TextureFormat format)
	{
		//�����֮ǰ������
		Clear();

		if (width > 0 && height > 0 && (format == TF_BGR24 || format == TF_DEPTH16))
		{
			switch (format)
			{
			case TF_BGR24:
				m_data = new BYTE[width * height * 3];
				m_pitch = width * 3;
				break;
			case TF_DEPTH16:
				m_data = new BYTE[width * height * 2];
				m_pitch = width * 2;
				break;
			default:
				break;
			}

			m_width = width;
			m_height = width;
			m_format = format;
		}
	}

}
