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

        int positionCount = 0;
        int texcoordCount = 0;
        int normalCount = 0;
        int triangleCount = 0;
        float x, y, z;
        int i1, i2, i3, i4, i5, i6, i7, i8, i9;

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
			}
            else if (sscanf(line, "v %f %f %f", &x, &y, &z) == 3)
            {
                ++positionCount;
            }
            else if (sscanf(line, "vt %f %f", &x, &y) == 2)
            {
                ++texcoordCount;
            }
            else if (sscanf(line, "vn %f %f %f", &x, &y, &z) == 3)
            {
                ++normalCount;
            }
            else if (sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &i1, &i2, &i3, &i4, &i5, &i6, &i7, &i8, &i9) == 9)
            {
                ++triangleCount;
            }
            else if (sscanf(line, "f %d//%d %d//%d %d//%d", &i1, &i2, &i3, &i4, &i5, &i6) == 6)
            {
                ++triangleCount;
            }
            else if (sscanf(line, "f %d/%d %d/%d %d/%d", &i1, &i2, &i3, &i4, &i5, &i6) == 6)
            {
                ++triangleCount;
            }
            else if (sscanf(line, "f %d %d %d", &i1, &i2, &i3) == 3)
            {
                ++triangleCount;
            }

            while (line < end && *line != 0) ++line;
            while (line < end && *line == 0) ++line;
		}

        if (triangleCount <= 0)
        {
            SLOG(fileName);
            Clear();
            return false;
        }

        vec3 *positions = NULL;
        if (positionCount > 0)
        {
            positions = new vec3[positionCount];
        }

        vec2 *texcoords = NULL;
        if (texcoordCount > 0)
        {
            texcoords = new vec2[texcoordCount];
        }

        vec3 *normals = NULL;
        if (normalCount > 0)
        {
            normals = new vec3[normalCount];
        }

        m_verticeCount = triangleCount * 3;
        m_vertices = new Vertex[m_verticeCount];

        line = obj_source;
        int p = 0, tc = 0, n = 0, v = 0;
        while (line < end)
        {
            while (line < end && (*line == ' ' || *line == '\t')) line++;

            if (sscanf(line, "v %f %f %f", &x, &y, &z) == 3)
            {
                x *= 0.03528;
                y *= 0.03528;
                z *= 0.03528;
                positions[p++] = vec3(x, y, z);
            }
            else if (sscanf(line, "vt %f %f", &x, &y) == 2)
            {
                texcoords[tc++] = vec2(x, y);
            }
            else if (sscanf(line, "vn %f %f %f", &x, &y, &z) == 3)
            {
                normals[n++] = normalize(vec3(x, y, z));
            }
            else if (sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &i1, &i2, &i3, &i4, &i5, &i6, &i7, &i8, &i9) == 9)
            {
                m_vertices[v].position = positions[i1 - 1];
                m_vertices[v].texcoord = texcoords[i2 - 1];
                m_vertices[v].normal = normals[i3 - 1];
                v++;
                m_vertices[v].position = positions[i4 - 1];
                m_vertices[v].texcoord = texcoords[i5 - 1];
                m_vertices[v].normal = normals[i6 - 1];
                v++;
                m_vertices[v].position = positions[i7 - 1];
                m_vertices[v].texcoord = texcoords[i8 - 1];
                m_vertices[v].normal = normals[i9 - 1];
                v++;
            }
            else if (sscanf(line, "f %d//%d %d//%d %d//%d", &i1, &i2, &i3, &i4, &i5, &i6) == 6)
            {
                m_vertices[v].position = positions[i1 - 1];
                m_vertices[v].normal = normals[i2 - 1];
                v++;
                m_vertices[v].position = positions[i3 - 1];
                m_vertices[v].normal = normals[i4 - 1];
                v++;
                m_vertices[v].position = positions[i5 - 1];
                m_vertices[v].normal = normals[i6 - 1];
                v++;
            }
            else if (sscanf(line, "f %d/%d %d/%d %d/%d", &i1, &i2, &i3, &i4, &i5, &i6) == 6)
            {
                m_vertices[v].position = positions[i1 - 1];
                if (texcoords != NULL && i1 - 1 < texcoordCount) m_vertices[v].texcoord = texcoords[i1 - 1];
                if (texcoords != NULL && i2 - 1 < texcoordCount) m_vertices[v].texcoord = texcoords[i2 - 1];
                if (normals != NULL && i1 - 1 < normalCount) m_vertices[v].normal = normals[i1 - 1];
                if (normals != NULL && i2 - 1 < normalCount) m_vertices[v].normal = normals[i2 - 1];
                v++;
                m_vertices[v].position = positions[i3 - 1];
                if (texcoords != NULL && i3 - 1 < texcoordCount) m_vertices[v].texcoord = texcoords[i3 - 1];
                if (texcoords != NULL && i4 - 1 < texcoordCount) m_vertices[v].texcoord = texcoords[i4 - 1];
                if (normals != NULL && i3 - 1 < normalCount) m_vertices[v].normal = normals[i3 - 1];
                if (normals != NULL && i4 - 1 < normalCount) m_vertices[v].normal = normals[i4 - 1];
                v++;
                m_vertices[v].position = positions[i5 - 1];
                if (texcoords != NULL && i5 - 1 < texcoordCount) m_vertices[v].texcoord = texcoords[i5 - 1];
                if (texcoords != NULL && i6 - 1 < texcoordCount) m_vertices[v].texcoord = texcoords[i6 - 1];
                if (normals != NULL && i5 - 1 < normalCount) m_vertices[v].normal = normals[i5 - 1];
                if (normals != NULL && i6 - 1 < normalCount) m_vertices[v].normal = normals[i6 - 1];
                v++;
            }
            else if (sscanf(line, "f %d %d %d", &i1, &i2, &i3) == 3)
            {
                m_vertices[v].position = positions[i1 - 1];
                if (texcoords != NULL && i1 - 1 < texcoordCount) m_vertices[v].texcoord = texcoords[i1 - 1];
                if (normals != NULL && i1 - 1 < normalCount) m_vertices[v].normal = normals[i1 - 1];
                v++;
                m_vertices[v].position = positions[i2 - 1];
                if (texcoords != NULL && i2 - 1 < texcoordCount) m_vertices[v].texcoord = texcoords[i2 - 1];
                if (normals != NULL && i2 - 1 < normalCount) m_vertices[v].normal = normals[i2 - 1];
                v++;
                m_vertices[v].position = positions[i3 - 1];
                if (texcoords != NULL && i3 - 1 < texcoordCount) m_vertices[v].texcoord = texcoords[i3 - 1];
                if (normals != NULL && i3 - 1 < normalCount) m_vertices[v].normal = normals[i3 - 1];
                v++;
            }

            while (line < end && *line != 0) line++;
            while (line < end && *line == 0) line++;
        }

        delete[] positions;
        delete[] normals;
        delete[] texcoords;

        for (int i = 0; i < m_verticeCount; ++i)
        {
            m_vertices[i].color = vec3(1.f);
        }

        if (normalCount <= 0)
        {
            vec3 a, b, normal;
            for (int i = 0; i < m_verticeCount; i += 3)
            {
                int i0 = i, i1 = i + 1, i2 = i + 2;

                a = m_vertices[i0].position - m_vertices[i1].position;
                b = m_vertices[i2].position - m_vertices[i0].position;

                normal = normalize(cross(a, b));

                m_vertices[i0].normal = normal;
                m_vertices[i1].normal = normal;
                m_vertices[i2].normal = normal;
            }
        }

        return true;
    }

    void Object::Translation(const vec3 &deltaPos)
    {
        for (int i = 0; i < m_verticeCount; ++i)
        {
            m_vertices[i].position += deltaPos;
        }
    }

    void Object::Scale(float scaleFactor)
    {
        for (int i = 0; i < m_verticeCount; ++i)
        {
            m_vertices[i].position *= scaleFactor;
        }
    }

    void Object::Rotate(float angle, const vec3 &axis)
    {
        mat3x3 rotationMatrix = mat3x3(rotate(angle, axis));

        for (int i = 0; i < m_verticeCount; ++i)
        {
            m_vertices[i].position = rotationMatrix * m_vertices[i].position;
        }
    }

    void Object::Clear()
    {
        m_texture.Clear();

        if (NULL != m_vertices)
        {
            delete[] m_vertices;
        }

        m_vertices = NULL;
        m_verticeCount = 0;
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

        bool success = true;

        //TODO 只有解析了map_Ka
        char *line = mtl_source;
        char *end = mtl_source + mtl_length;
        while (line < end)
        {
            while (line < end && (*line == ' ' || *line == '\t'))
            {
                ++line;
            }

            std::string temp(line, 6);
            if (temp.compare("map_Ka") == 0 && (line[6] == ' ' || line[6] == '\t'))
            {
                char *textureFileName = line + 6;
                while (textureFileName < end && (*textureFileName == ' ' || *textureFileName == '\t'))
                {
                    ++textureFileName;
                }

                success = m_texture.LoadTexture(textureFileName);
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

        return success;
    }

}