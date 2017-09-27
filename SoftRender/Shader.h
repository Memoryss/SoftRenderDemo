#ifndef __SHADER_H__
#define __SHADER_H__

#include "type.h"
#include "SoftwareRenderState.h"

namespace SoftRenderer
{
    struct RasterizerVertex;
    struct Vertex;
    class SoftRender;
    class Texture;

    class Shader
    {
    public:
        virtual ~Shader() {}

        virtual void VertexShader(RasterizerVertex *v_out, const Vertex *v_in) = 0;
        virtual bool FragmentShader(RasterizerVertex *v_io) = 0;

        void SetProjMatrix(const mat4x4 &mat)
        {
            m_projMatrix = mat;
        }

        void SetSampleState(const SamplerState &state)
        {
            m_state = state;
        }

        void SetTexture(Texture *texture)
        {
            m_texture = texture;
        }
    protected:
        mat4x4 m_projMatrix;
        Texture *m_texture{ NULL };
        SamplerState m_state;

    };
}

#endif
