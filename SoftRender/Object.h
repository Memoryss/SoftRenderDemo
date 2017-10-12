#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <vector>

#include "type.h"
#include "Texture.h"
#include "Vertex.h"
#include "Material.h"

namespace SoftRenderer
{
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

        //TODO 使用顶点索引
        bool Load(const char *fileName);

        void Translation(const vec3 &deltaPos);

        void Scale(float scaleFactor);

        void Rotate(float angle, const vec3 &axis);

        void Clear();

    private:

        bool loadResource(const char *dir, const char *fileName, char **source, long length);

        bool loadMaterial(const char *mtlFileName);

    public:
        Texture m_texture; //TODO 暂时只有map_ka 纹理
        //Vertex *m_vertices{ NULL };
        //int m_verticeCount{ 0 };
        //int *m_indices{ NULL };
        //int m_indiceCount{ 0 };

        //std::vector<Vertex> m_vertices; //顶点
        std::vector<vec3> m_positions;
        std::vector<vec3> m_normals;
        std::vector<vec2> m_texcoods;
        std::vector<Face> m_faces;
        std::vector<Material> m_materials;
    };
}

#endif