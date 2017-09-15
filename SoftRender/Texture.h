#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "type.h"

namespace SoftRenderer {

    enum class TextureFormat
    {
        TF_NONE = 0,
        TF_BGR24,
        TF_DEPTH16,
    };

    class Texture
    {
    public:

        Texture();
        ~Texture();

        bool LoadTexture(const char *textureFileName);

        void Create(int width, int height, int format);

        void GetColorNearest(float s, float t, vec3 &color);
        void GetColorBilinear(float s, float t, vec3 &color);

        float GetShadowNearest(vec4 &texcoord);
        float GetShadowBilinear(vec4 &texcoord);

        void Destory();

        int GetWidth() const;
        int GetHeight() const;
        void * GetData() const;
        TextureFormat GetFormat() const;

    private:
        void init();

    private:
        void *m_data;   //����

        int m_width;    //���
        int m_height;   //�߶�
        TextureFormat m_format;   //��ʽ
        int m_pitch;    //ƫ��
    };

}

#endif