#ifndef __SOFTWARE_RENDER_API_H__
#define __SOFTWARE_RENDER_API_H__

#include "type.h"

namespace SoftRenderer
{
    class FrameBuffer;
    class Light;
    class Texture;
    class Vertex;


    enum AntiAliasingType
    {
        AAT_2X2 = 0,
        AAT_3X3,
        AAT_4X4,
    };

    enum CullFaceType
    {
        CFT_FRONT = 0,
        CFF_BACK,
    };

    class SoftwareRenderAPI
    {
    public:
        SoftwareRenderAPI();
        ~SoftwareRenderAPI();


    private:
        int m_width;
        int m_height;

        int m_viewportX;
        int m_viewportY;
        int m_viewportWidth;
        int m_vewportHeight;

        BYTE *m_antiAliasingColorBuffer;
        int m_antiAliasingColorBufferWidth;
        int m_m_antiAliasingColorBufferHeight;

        BYTE *m_standardColorBuffer;
        int m_standardColorBufferWidth;
        int m_standardColorBufferHeight;

        BITMAPINFO m_bitmap;

        BYTE *m_standardDepthBuffer;
        int m_standardDepthBufferWidth;
        int m_standardDepthBufferHeight;

        BYTE *m_depthBuffer;
        int m_depthBufferWidth;
        int m_depthBufferHeight;

        BYTE *m_colorBuffer;
        int m_colorBufferWidth;
        int m_colorBufferHeight;

        FrameBuffer *m_frameBuffer;

        AntiAliasingType m_aniAliasingType;

        mat4x4 m_mvpMatrix;
        mat4x4 m_shadowMapMatrix;

        Light *m_light;

        CullFaceType m_cullFaceType;

        bool m_bilinearTextureFiltering;
        bool m_depthTest;

        Texture *m_texture;
        Texture *m_shadowMap;

        Vertex *m_vertices;
    };
}

#endif