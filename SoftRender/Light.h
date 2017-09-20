#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "type.h"

namespace SoftRenderer
{
    class Light
    {
    public:
        vec3 m_position{ 0.f, 0.f, 0.f };        //位置
        vec3 m_ambient{ 0.f, 0.f, 0.f };         //镜面反射
        vec3 m_diffuse{ 1.f, 1.f, 1.f };         //漫反射
        float m_constAttention{ 1.f };         //常量衰减
        float m_linearAttention{ 0.f };        //线性衰减
        float m_quadraticAttention{ 0.f };     //二次衰减
    };
}

#endif
