#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "type.h"

namespace SoftRenderer
{
    struct Material
    {
        vec3 emissive{ 0.f, 0.f, 0.f};  //  �Է���
        vec3 ambient{ 0.f, 0.f, 0.f };   //  ������
        vec3 diffuse{ 1.f, 1.f, 1.f };   //  ������
        vec3 specular{ 0.f, 0.f, 0.f };  //  ���淴��
        float specularPower{ 20 };    // ���淴��ǿ��

        std::string diffuseTextureName;
        std::string specularTextureName;
        std::string ambientTextureName;
        std::string emissiveTextureName;
        float m_alpha{ 1.f };
        float m_shineness{ 1.f };
    };
}

#endif