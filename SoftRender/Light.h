#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "type.h"

namespace SoftRenderer
{
    enum LightType
    {
        NONE = 0,
        POINT,
        SPOT,
        DIRECTION,
    };

    class Light
    {
    public:
        vec3 m_position{ 0.f, 0.f, 0.f };        //λ��
        vec3 m_ambient{ 0.f, 0.f, 0.f };         //������
        vec3 m_specular{ 0.f, 0.f, 0.f };        //�����
        vec3 m_diffuse{ 1.f, 1.f, 1.f };         //������
        //ƽ�й�����
        vec3 m_direction{ 0.f, 0.f, 1.f };
        //�������
        float m_attenStart{ 0 };
        float m_attenEnd{ 1 };
        float m_attenFallOff{ 1.f };
        float m_constAttention{ 1.f };         //����˥��
        float m_linearAttention{ 0.f };        //����˥��
        float m_quadraticAttention{ 0.f };     //����˥��
        //�۹��
        float m_spotInner{ 0 };
        float m_spotOuter{ 90 };
        float m_spotFallOff{ 1 };

        LightType m_type = NONE;                       //��Դ����
    };
}

#endif
