#ifndef __SOFTWARE_RENDER_H__
#define __SOFTWARE_RENDER_H__

#include <windows.h>
#include <vector>
#include "type.h"
#include "SoftwareRenderContext.h"
#include "SoftwareRenderState.h"
#include "Vertex.h"
#include "Texture.h"

namespace SoftRenderer
{
    class FrameBuffer;
    struct RenderBuffer;
    class Light;
    class Camera;
    class Shader;
    class Object;
    struct Material;

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

        void SetMaterial(Material *material);

        void SetShader(Shader *shader);

        void SetRenderState(const SoftwareRenderState &state);

        void SetSampleState(const SamplerState &state);

        void Render(RenderBuffer *buffer);

        void Render(Object *object);

        void Begin();

        void End();

        void Present();

    protected:
        void rasterizePoint(const RasterizerVertex *point);

        void rasterizeLine(const RasterizerVertex *pointA, const RasterizerVertex *pointB);

        void rasterizeTriangle(const RasterizerVertex *pointA, const RasterizerVertex *pointB, const RasterizerVertex *pointC);

        bool cullBackFace(const RasterizerVertex *pa, const RasterizerVertex *pb, const RasterizerVertex *pc);

        void vertexShader(RasterizerVertex *v_out, const Vertex *v_in);

        bool fragmentShader(RasterizerVertex *v);

        void output(int x, int y, const RasterizerVertex *v);

        bool depthTest(float oldDepth, float newDepth);

    private:
        SoftwareRenderContext *m_context{ NULL };

        vec3 *m_colorBuffer{ NULL };
        float *m_depthBuffer{ NULL };
        int m_width{ 0 };
        int m_height{ 0 };

        mat4x4 m_worldMatrix{ mat4x4(1.f) };
        mat4x4 m_viewMatrix{ mat4x4(1.f) };
        mat4x4 m_projMatrix{ mat4x4(1.f) };

        Texture *m_texture{ NULL };
        Camera *m_camera{ NULL };
        Light *m_light{ NULL };
        Material *m_material{ NULL };

        SoftwareRenderState m_renderState;
        Shader *m_shader{ NULL };

        SamplerState m_samplerState;

        std::vector<RasterizerVertex> m_rasterVertexBuffer;
    };
}

#endif