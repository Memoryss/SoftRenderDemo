#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "type.h"

namespace SoftRenderer
{
    class Light
    {
    public:
        vec3 m_position{ 0.f, 0.f, 0.f };        //λ��
        vec3 m_ambient{ 0.f, 0.f, 0.f };         //���淴��
        vec3 m_diffuse{ 1.f, 1.f, 1.f };         //������
        float m_constAttention{ 1.f };         //����˥��
        float m_linearAttention{ 0.f };        //����˥��
        float m_quadraticAttention{ 0.f };     //����˥��
    };
}

#endif
