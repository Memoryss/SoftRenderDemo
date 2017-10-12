#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "type.h"

namespace SoftRenderer {

    struct Material;

    struct Vertex
    {
        vec3 position;
        vec3 normal;
        vec4 color;
        vec2 texcoord;
    };

    //TODOֻ֧��������
    struct Face
    {
        std::vector<int> m_posIndices;
        std::vector<int> m_normalIndices;
        std::vector<int> m_texcoordIndices;

        Material *m_material;
    };

    struct RasterizerVertex
    {
        vec4 position;
        vec4 originPostion; //  ��¼��ʼλ�� Ϊ�˼������ģ��
        vec3 normal;
        vec4 color;
        vec2 texcoord;

        static void Lerp(RasterizerVertex &v, const RasterizerVertex &a, const RasterizerVertex &b, float ratio)
        {
            v.position = a.position + (b.position - a.position) * ratio;
            v.normal = a.normal + (b.normal - a.normal) * ratio;
            v.color = a.color + (b.color - a.color) * ratio;
            v.texcoord = a.texcoord + (b.texcoord - a.texcoord) * ratio;
            v.originPostion = a.originPostion + (b.originPostion - a.originPostion) * ratio;
        }
    };

}

#endif

