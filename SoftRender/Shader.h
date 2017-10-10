#ifndef __SHADER_H__
#define __SHADER_H__

#include "type.h"
#include "SoftwareRenderState.h"
#include "Light.h"
#include "Material.h"

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

        void SetViewMatrix(const mat4x4 &mat)
        {
            m_viewMatrix = mat;
        }

        void SetWorldMatrix(const mat4x4 &mat)
        {
            m_worldMatrix = mat;
        }

        void SetSampleState(const SamplerState &state)
        {
            m_state = state;
        }

        void SetTexture(Texture *texture)
        {
            m_texture = texture;
        }

        void SetLight(Light *light)
        {
            m_light = light;
        }

        void SetMaterial(Material *material)
        {
            m_material = material;
        }

        void SetCameraPosition(const vec3 &camepos)
        {
            m_camPos = camepos;
        }

    protected:
        vec3 m_camPos{ 0.f, 0.f, 0.f };
        mat4x4 m_projMatrix;
        mat4x4 m_viewMatrix;
        mat4x4 m_worldMatrix;
        Texture *m_texture{ NULL };
        SamplerState m_state;
        Light *m_light{ NULL };
        Material *m_material{ NULL };
    };
}

#endif
