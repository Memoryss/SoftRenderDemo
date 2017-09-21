#ifndef __SHADER_H__
#define __SHADER_H__

namespace SoftRenderer
{
    struct RasterizerVertex;
    struct Vertex;
    class SoftRender;

    class Shader
    {
    public:
        virtual ~Shader() {}

        virtual void VertexShader(RasterizerVertex *v_out, const Vertex *v_in) = 0;
        virtual bool FragmentShader(RasterizerVertex *v_io) = 0;
    };
}

#endif
