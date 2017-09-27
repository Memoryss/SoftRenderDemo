#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "type.h"

namespace SoftRenderer {

    struct Vertex
    {
        vec3 position;
        vec3 normal;
        vec4 color;
        vec2 texcoord;
    };

    struct RasterizerVertex
    {
        vec4 position;
        vec3 normal;
        vec4 color;
        vec2 texcoord;

        static void Lerp(RasterizerVertex &v, const RasterizerVertex &a, const RasterizerVertex &b, float ratio)
        {
            v.position = a.position + (b.position - a.position) * ratio;
            v.normal = a.normal + (b.normal - a.normal) * ratio;
            v.color = a.color + (b.color - a.color) * ratio;
            v.texcoord = a.texcoord + (b.texcoord - a.texcoord) * ratio;
        }
    };

}

#endif

