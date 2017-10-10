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
        vec3 m_position{ 0.f, 0.f, 0.f };        //位置
        vec3 m_ambient{ 0.f, 0.f, 0.f };         //环境光
        vec3 m_specular{ 0.f, 0.f, 0.f };        //镜面光
        vec3 m_diffuse{ 1.f, 1.f, 1.f };         //漫反射
        //平行光属性
        vec3 m_direction{ 0.f, 0.f, 1.f };
        //点光属性
        float m_attenStart{ 0 };
        float m_attenEnd{ 1 };
        float m_attenFallOff{ 1.f };
        float m_constAttention{ 1.f };         //常量衰减
        float m_linearAttention{ 0.f };        //线性衰减
        float m_quadraticAttention{ 0.f };     //二次衰减
        //聚光灯
        float m_spotInner{ 0 };
        float m_spotOuter{ 90 };
        float m_spotFallOff{ 1 };

        LightType m_type = NONE;                       //光源类型
    };
}

#endif
