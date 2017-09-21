#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "type.h"

namespace SoftRenderer
{
    struct Material
    {
        vec3 emissive{ 0.f, 0.f, 0.f};  //  自发光
        vec3 ambient{ 1.f, 1.f, 1.f };   //  环境光
        vec3 diffuse{ 1.f, 1.f, 1.f };   //  漫反射
        vec3 specular{ 0.f, 0.f, 0.f };  //  镜面反射
        float specularPower{ 40 };    // 镜面反射强度
    };
}

#endif