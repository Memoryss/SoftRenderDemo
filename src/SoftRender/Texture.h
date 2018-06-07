#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "type.h"

namespace SoftRenderer {

    enum TextureFormat
    {
        UNKNOWN = 0,
        A8,
        R8G8B8,
        R8G8B8A8,
        D16,
	};

    enum TextureFilter
    {
        NEAREST = 0,//最近点
        LINEAR, //线性
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
        TextureFilter m_filter{ LINEAR };
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
        void reset();

        vec4 getColor(int u, int v);

        /*
        //最近点过滤
        void getColorNearest(int s, int t, vec4 &color);
        //双线性过滤
        void getColorBilinear(float s, float t, vec4 &color);
        */

    private:
        void *m_data{ NULL };   //数据

        int m_width{ 0 };    //宽度
        int m_height{ 0 };   //高度
        TextureFormat m_format{ UNKNOWN };   //格式
    };

}

#endif