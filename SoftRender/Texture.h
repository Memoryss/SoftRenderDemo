#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "type.h"

namespace SoftRenderer {

    enum TextureFormat
    {
        TF_NONE = 0,
        TF_BGR24,
        TF_DEPTH16,
    };

	enum PixelSize
	{
		PS_24 = 24,
		PS_32 = 32,
	};

    enum TextureFilter
    {
        NEAREST = 0,//�����
        Bilinear, //˫����
    };

    enum TextureWrapMode
    {
        WRAP = 0,
        CLAMP,
        BORAD,
    };

    struct SamplerState
    {
        TextureWrapMode m_wrapMode{ WRAP };
        TextureFilter m_filter{ Bilinear };
        vec4 m_boardColor{ 0.f, 0.f, 0.f, 1.f };
    };

    class Texture
    {
    public:

        Texture();
        ~Texture();

        bool LoadTexture(const char *textureFileName);

		void CreateTexture(int width, int height, TextureFormat format);

        void Sample2D(float x, float y, const SamplerState &state, vec4 &color);

        float GetShadowNearest(vec4 &texcoord);
        float GetShadowBilinear(vec4 &texcoord);

        void Clear();

        int GetWidth() const;
        int GetHeight() const;
        void * GetData() const;
        TextureFormat GetFormat() const;

    private:
        void init();

        //��������
        void getColorNearest(int s, int t, vec4 &color);
        //˫���Թ���
        void getColorBilinear(int s, int t, vec4 &color);

    private:
        void *m_data;   //����

        int m_width;    //���
        int m_height;   //�߶�
        TextureFormat m_format;   //��ʽ
        int m_pitch;    //ƫ��
    };

}

#endif