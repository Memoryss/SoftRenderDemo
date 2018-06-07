#ifndef __RENDER_BUFFER_H__
#define __RENDER_BUFFER_H__

#include <vector>
#include "Vertex.h"

namespace SoftRenderer
{
    enum PrimitiveType
    {
        PT_PointList = 0,
        PT_LineList,
        PT_TriangleList,
    };

    struct RenderBuffer
    {
        std::vector<Vertex> vbuffer;
        std::vector<short> ibuffer;
        PrimitiveType primType;
        int primCount;
    };
}

#endif
