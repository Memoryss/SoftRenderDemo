#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "type.h"

namespace SoftRenderer
{
    class Light
    {
    public:
        vec3 m_position;        //位置
        vec3 m_ambient;         //镜面反射
        vec3 m_diffuse;         //漫反射
        float m_constAttention;         //常量衰减
        float m_linearAttention;        //线性衰减
        float m_quadraticAttention;     //二次衰减
    };
}

#endif
