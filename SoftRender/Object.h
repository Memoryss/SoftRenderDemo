#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "type.h"
#include "Texture.h"

namespace SoftRenderer
{
    struct Vertex
    {
        vec3 m_position;
        vec3 m_color;
        vec2 m_texcoord;
        vec3 m_normal;
    };

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

        bool Load(const char *dir, const char *filePath);

        void Translation(const vec3 &deltaPos);

        void Scale(float scaleFactor);

        void Rotate(float angle, const vec3 &axis);

        void Clear();

    private:
        void init();

        bool loadResource(const char *dir, const char *fileName, char **source, long length);

        bool loadMaterial(const char *dir, const char *mtlFileName);

    public:
        Texture m_texture;
        Vertex *m_vertices;
        int m_verticeCount;
    };
}

#endif