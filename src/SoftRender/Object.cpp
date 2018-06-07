#include "Object.h"

#include <cstdio>
#include "log.h"
#include "ResourceManager.h"
#include "Vertex.h"

namespace SoftRenderer
{

    Object::Object()
    {

    }

    Object::~Object()
    {

    }

    bool Object::Load(const char *fileName)
    {
        std::string errorText("Error loading file %s!\r\n");

        Clear();

        //TODO 暂时为文本文件
        std::shared_ptr<IFile> file = ResourceManager::Instance()->OpenFile(fileName);
        
        if (!file)
        {
            SLOG(errorText + fileName + " load error");
            return false;
        }

        long obj_length = file->Size();
        char *obj_source = (char *)file->GetData();
        obj_length = file->Read(obj_source, obj_length);
        if (obj_length == 0 || obj_source == NULL)
        {
            SLOG(errorText + fileName + " read error");
            return false;
        }
        
        for (int i = 0; i < obj_length; ++i)
        {
            if (obj_source[i] == '\r' || obj_source[i] == '\n')
            {
                obj_source[i] = 0;
            }
        }

		char *line = obj_source;
		char *end = obj_source + obj_length;

        float x, y, z;
        int i1, i2, i3, i4, i5, i6, i7, i8, i9;

        Material *material = NULL;

		while (line < end)
		{
			while (line < end && (*line == ' ' || *line == '\t'))
			{
				++line;
			}

			std::string temp(line, 6);
			if (temp.compare("mtllib") ==0 &&(line[6] == ' ' || line[6] == '\t'))
			{
                char *mtlFileName = line + 6;
                while (mtlFileName < end && (*mtlFileName == ' ' || *mtlFileName == '\t'))
                {
                    ++mtlFileName;
                }
                if (!loadMaterial(mtlFileName))
                {
                    return false;
                }
                material = &m_materials[m_materials.size() - 1];
			}
            else if (sscanf(line, "v %f %f %f", &x, &y, &z) == 3)
            {
                m_positions.push_back(vec3(x, y, z));
            }
            else if (sscanf(line, "vt %f %f", &x, &y) == 2)
            {
                m_texcoods.push_back(vec2(x, y));
            }
            else if (sscanf(line, "vn %f %f %f", &x, &y, &z) == 3)
            {
                m_normals.push_back(vec3(x, y, z));
            }
            else if (sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &i1, &i2, &i3, &i4, &i5, &i6, &i7, &i8, &i9) == 9)
            {
                Face face;
                face.m_posIndices.push_back(i1 - 1);
                face.m_texcoordIndices.push_back(i2 - 1);
                face.m_normalIndices.push_back(i3 - 1);
                face.m_posIndices.push_back(i4 - 1);
                face.m_texcoordIndices.push_back(i5 - 1);
                face.m_normalIndices.push_back(i6 - 1);
                face.m_posIndices.push_back(i7 - 1);
                face.m_texcoordIndices.push_back(i8 - 1);
                face.m_normalIndices.push_back(i9 - 1);
                face.m_material = material;
                m_faces.push_back(face);
            }
            else if (sscanf(line, "f %d//%d %d//%d %d//%d", &i1, &i2, &i3, &i4, &i5, &i6) == 6)
            {
                //TODO
            }
            else if (sscanf(line, "f %d/%d %d/%d %d/%d", &i1, &i2, &i3, &i4, &i5, &i6) == 6)
            {
//                 Face face;
//                 face.m_posIndices.push_back(i1 - 1);
//                 face.m_posIndices.push_back(i3 - 1);
//                 face.m_posIndices.push_back(i5 - 1);
//                 face.m_texcoordIndices.push_back(i1 - 1);
//                 face.m_texcoordIndices.push_back(i2 - 1);
//                 face.m_texcoordIndices.push_back(i6 - 1);
//                 face.m_normalIndices.push_back(i7 - 1);
//                 face.m_normalIndices.push_back(i8 - 1);
//                 face.m_normalIndices.push_back(i9 - 1);
//                 face.m_material = material;
//                 m_faces.push_back(face);
            }
            else if (sscanf(line, "f %d %d %d", &i1, &i2, &i3) == 3)
            {
                Face face;
                face.m_posIndices.push_back(i1 - 1);
                face.m_posIndices.push_back(i2 - 1);
                face.m_posIndices.push_back(i3 - 1);
                face.m_material = material;
                m_faces.push_back(face);
            }

            while (line < end && *line != 0) ++line;
            while (line < end && *line == 0) ++line;
		}

        if (m_positions.size() <= 0)
        {
            SLOG(fileName);
            Clear();
            return false;
        }

        //如果没有法线 需要手动计算
        if (m_normals.size() <= 0)
        {
            vec3 a, b, normal;
            //TODO 只支持三角形
            for (int i = 0; i < m_faces.size(); ++i)
            {
                int i0 = i, i1 = i + 1, i2 = i + 2;

                a = m_positions[m_faces[i].m_posIndices[1]] - m_positions[m_faces[i].m_posIndices[0]];
                b = m_positions[m_faces[i].m_posIndices[2]] - m_positions[m_faces[i].m_posIndices[0]];

                normal = normalize(cross(a, b));

                m_normals.push_back(normal);
                m_faces[i].m_normalIndices.push_back(m_normals.size() - 1);
                m_faces[i].m_normalIndices.push_back(m_normals.size() - 1);
                m_faces[i].m_normalIndices.push_back(m_normals.size() - 1);
            }
        }

        return true;
    }

    void Object::Translation(const vec3 &deltaPos)
    {
        for (int i = 0; i < m_positions.size(); ++i)
        {
            m_positions[i] += deltaPos;
        }
    }

    void Object::Scale(float scaleFactor)
    {
        for (int i = 0; i < m_positions.size(); ++i)
        {
            m_positions[i] *= scaleFactor;
        }
    }

    void Object::Rotate(float angle, const vec3 &axis)
    {
        mat3x3 rotationMatrix = mat3x3(rotate(angle, axis));

        for (int i = 0; i < m_positions.size(); ++i)
        {
            m_positions[i] = rotationMatrix * m_positions[i];
        }

        for (int i = 0; i < m_normals.size(); ++i)
        {
            m_normals[i] = rotationMatrix * m_normals[i];
        }
    }

    void Object::Clear()
    {
        m_texture.Clear();

        m_positions.clear();
        m_texcoods.clear();
        m_normals.clear();
        m_materials.clear();
        m_faces.clear();
    }

    bool Object::loadResource(const char *dir, const char *fileName, char **source, long length)
    {
        std::string filePath = dir;
        filePath += fileName;
		std::string errorText("Error open file ");
        FILE *file = fopen(filePath.c_str(), "rb");
        if (file == NULL)
        {
			SLOG(errorText + filePath);
			return false;
        }

		fseek(file, 0, SEEK_END);
		length = ftell(file);
		fseek(file, 0, SEEK_SET);

		*source = new char[length + 1];
		fread(*source, 1, length, file);
		(*source)[length] = 0;

		fclose(file);

		for (int i = 0; i < length; ++i)
		{
			if ((*source)[i] == '\r' || (*source)[i] == '\n')
			{
				(*source)[i] = 0;
			}
		}

        return true;
    }

    bool Object::loadMaterial(const char *mtlFileName)
    {
        std::shared_ptr<IFile> file = ResourceManager::Instance()->OpenFile(mtlFileName);
        if (!file)
        {
            return false;
        }

        long mtl_length = file->Size();
        char *mtl_source = (char *)file->GetData();
        mtl_length = file->Read(mtl_source, mtl_length);
        if (mtl_length == 0 || mtl_source == NULL)
        {
            return false;
        }

        for (int i = 0; i < mtl_length; ++i)
        {
            if (mtl_source[i] == '\r' || mtl_source[i] == '\n')
            {
                mtl_source[i] = 0;
            }
        }

        Material material;

        char *line = mtl_source;
        char *end = mtl_source + mtl_length;
        while (line < end)
        {
            while (line < end && (*line == ' ' || *line == '\t'))
            {
                ++line;
            }

            char name[100] = {0};
            float x, y, z;
            if (sscanf(line, "Ka %f %f %f", &x, &y, &z) == 3)
            {
                material.ambient = vec3(x, y, z);
            }
            else if (sscanf(line, "Kd %f %f %f", &x, &y, &z) == 3)
            {
                material.diffuse = vec3(x, y, z);
            }
            else if (sscanf(line, "Ks %f %f %f", &x, &y, &z) == 3)
            {
                material.specular = vec3(x, y, z);
            }
            else if (sscanf(line, "Ke %f %f %f", &x, &y, &z) == 3)
            {
                material.emissive = vec3(x, y, z);
            }
            else if (sscanf(line, "map_Ka %[^\n]", &name) == 1)
            {
                material.ambientTextureName = name;
            }
            else if (sscanf(line, "map_Kd %[^\n]", &name) == 1)
            {
                material.diffuseTextureName = name;
            }
            else if (sscanf(line, "map_Ke %[^\n]", &name) == 1)
            {
                material.ambientTextureName = name;
            }
            else if (sscanf(line, "map_Ks %[^\n]", &name) == 1)
            {
                material.ambientTextureName = name;
            }
            else if (sscanf(line, "d %f", &x) == 1)
            {
                material.m_alpha = x;
            }
            else if (sscanf(line, "Ns %f", &x) == 1)
            {
                material.m_shineness = x;
            }

            while (line < end && *line != 0)
            {
                ++line;
            }
            while (line < end && *line == 0)
            {
                ++line;
            }
        }

        m_materials.push_back(material);
        return true;
    }

}