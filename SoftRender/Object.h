#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "type.h"
#include "Texture.h"

namespace SoftRenderer
{
    struct Vertex;

    struct Triangle
    {
        vec4 m_positions[3];
        vec3 m_colors[3];
        vec3 m_texcoord[3];
    };

    class Object
    {
    public:
        Object();
        ~Object();

        //TODO ʹ�ö�������
        bool Load(const char *fileName);

        void Translation(const vec3 &deltaPos);

        void Scale(float scaleFactor);

        void Rotate(float angle, const vec3 &axis);

        void Clear();

    private:

        bool loadResource(const char *dir, const char *fileName, char **source, long length);

        bool loadMaterial(const char *mtlFileName);

    public:
        Texture m_texture; //TODO ��ʱֻ��map_ka ����
        Vertex *m_vertices{ NULL };
        int m_verticeCount{ 0 };
    };
}

#endif