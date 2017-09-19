#ifndef __SOFTWARE_RENDER_H__
#define __SOFTWARE_RENDER_H__

#include "type.h"
#include "Light.h"
#include "Object.h"
#include "Camera.h"

namespace SoftRenderer
{
    class FrameBuffer;
    class Texture;
    class Vertex;

    class SoftwareRender
    {
    public:
        SoftwareRender();
        ~SoftwareRender();

        //初始场景
        bool InitScene();

        void Render(float frameTime);
        void Resize(int width, int height);
        void Clear();

        void SetMVPMatrix(mat4x4 matrix);

        void SetLight(const Light &light);

        void DrawTriangles(Vertex *vertices, int index, int count);

        void ClipTriangle(Triangle &triangle);

        //处理事件

    private:
		int m_width{ 0 };
		int m_height{ 0 };

		int m_viewportX{ 0 };
		int m_viewportY{ 0 };
		int m_viewportWidth{ 0 };
		int m_viewportHeight{ 0 };

		BYTE *m_antiAliasingColorBuffer{ NULL };
		int m_antiAliasingColorBufferWidth{ 0 };
		int m_antiAliasingColorBufferHeight{ 0 };

		BYTE *m_standardColorBuffer{ NULL };
		int m_standardColorBufferWidth{ 0 };
		int m_standardColorBufferHeight{ 0 };

        BITMAPINFO m_bitmap;

		BYTE *m_standardDepthBuffer{ NULL };
		int m_standardDepthBufferWidth{ 0 };
		int m_standardDepthBufferHeight{ 0 };

		BYTE *m_depthBuffer{ NULL };
		int m_depthBufferWidth{ 0 };
		int m_depthBufferHeight{ 0 };

		BYTE *m_colorBuffer{ NULL };
		int m_colorBufferWidth{ 0 };
		int m_colorBufferHeight{ 0 };

		FrameBuffer *m_frameBuffer{ NULL };

		mat4x4 m_mvpMatrix{ mat4x4(1.f) };
		mat4x4 m_shadowMapMatrix{ mat4x4(1.f) };

		Light *m_light;

		bool m_bilinearTextureFiltering{ true };
		bool m_depthTest{ false };

        Texture *m_texture{ NULL };
		Texture *m_shadowMap{ NULL };

		Vertex *m_vertices{ NULL };

        Object m_object;

        Camera m_camera;
    };
}

#endif