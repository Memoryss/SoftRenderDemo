#include "Texture.h"

#include <string>
#include "FreeImage.h"

namespace SoftRenderer {

    Texture::Texture()
    {
        init();
    }

    Texture::~Texture()
    {

    }

    bool Texture::LoadTexture(const char *textureFileName)
    {
        FREE_IMAGE_FORMAT image_format = FreeImage_GetFileType(textureFileName);
        if (FIF_UNKNOWN == image_format)
        {
            image_format = FreeImage_GetFIFFromFilename(textureFileName);
        }

        if (FIF_UNKNOWN == image_format)
        {
            
            return false;
        }
    }

    void Texture::Create(int width, int height, int format)
    {

    }

    void Texture::GetColorNearest(float s, float t, vec3 &color)
    {

    }

    void Texture::GetColorBilinear(float s, float t, vec3 &color)
    {

    }

    float Texture::GetShadowNearest(vec4 &texcoord)
    {

    }

    float Texture::GetShadowBilinear(vec4 &texcoord)
    {

    }

    void Texture::Destory()
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

}
