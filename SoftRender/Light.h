#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "type.h"

namespace SoftRenderer
{
    class Light
    {
    public:
        vec3 m_position;        //λ��
        vec3 m_ambient;         //���淴��
        vec3 m_diffuse;         //������
        float m_constAttention;         //����˥��
        float m_linearAttention;        //����˥��
        float m_quadraticAttention;     //����˥��
    };
}

#endif
