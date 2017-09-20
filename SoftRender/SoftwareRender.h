#ifndef __SOFTWARE_RENDER_H__
#define __SOFTWARE_RENDER_H__

#include "type.h"
#include "Light.h"
#include "Object.h"
#include "Camera.h"
#include "SoftwareRenderState.h"

namespace SoftRenderer
{
    class FrameBuffer;
    class Texture;
    class Vertex;

    class SoftwareRender
    {
    public:
        SoftwareRender(HWND hwnd, int w, int h);
        ~SoftwareRender();

        void Resize(int width, int height);

        void Clear(const vec3 &color = vec3(0.f, 0.f, 0.f), float depth = 1.f);

        void SetWorldMatrix(const mat4x4 &m);

        void SetViewMatrix(const mat4x4 &m);

        void SetProjMatrix(const mat4x4 &m);

        void SetCamera(Camera *cam);

        void SetLight(Light *light);

        void SetTexture(Texture *texture);

        void SetRenderState(const SoftwareRenderState &state);

        void Render();

        void Begin();

        void End();

        void Present();

    protected:
        void rasterizePoint();

        void rasterizeLine();

        void rasterizeTriangle();

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

        Camera *m_camera;

        SoftwareRenderState m_renderState;
    };
}

#endif