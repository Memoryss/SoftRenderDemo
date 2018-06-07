#include "AABB.h"

namespace SoftRenderer {

    AABB::AABB() : m_max(-INT_MAX, -INT_MAX, -INT_MAX), m_min(INT_MAX, INT_MAX, INT_MAX)
    {
    }

    AABB::AABB(const vec3 & min, const vec3 & max) : m_min(min), m_max(max)
    {

    }

    AABB::AABB(const AABB & box) : m_min(box.m_min), m_max(box.m_max)
    {
        
    }

    AABB::AABB(vec3 * vertices, uint32_t count)
    {
        UpdateAABB(vertices, count);
    }

    AABB::~AABB()
    {

    }

    void AABB::UpdateAABB(vec3 * vertices, uint32_t count)
    {
        if (!vertices || count)
        {
            return;
        }

        uint32_t min_index = 0, max_index = 0;
        computeDisByDir(vec3(1, 0, 0), vertices, count, min_index, max_index);
        m_min.x = vertices[min_index].x;
        m_max.x = vertices[max_index].x;

        computeDisByDir(vec3(0, 1, 0), vertices, count, min_index, max_index);
        m_min.y = vertices[min_index].y;
        m_max.y = vertices[max_index].y;

        computeDisByDir(vec3(0, 0, 1), vertices, count, min_index, max_index);
        m_min.z = vertices[min_index].z;
        m_max.z = vertices[max_index].z;
    }

    void AABB::computeDisByDir(const vec3 & dir, vec3 * vertices, uint32_t count, uint32_t & min, uint32_t & max)
    {
        float maxProj = -FLT_MAX, minProj = FLT_MAX;
        for (uint32_t i = 0; i < count; ++i)
        {
             float proj = dot(vertices[i], dir);
             if (proj > maxProj)
             {
                 maxProj = proj;
                 max = i;
             }

             if (proj < minProj)
             {
                 minProj = proj;
                 min = i;
             }
        }
    }

    Intersection AABB::IsIntersect(const vec3 & point)
    {
        if (point.x < m_min.x || point.x > m_max.x || point.y < m_min.y || point.y > m_max.y || point.z < m_min.z || point.z > m_max.z)
        {
            return OUTSIDE;
        }
        else
        {
            return INSIDE;
        }
    }

    Intersection AABB::IsIntersect(const AABB & box)
    {
        if (box.m_max.x < m_min.x || box.m_min.x < m_max.x || box.m_max.y < m_min.y || box.m_min.y > m_max.y || box.m_max.z < m_min.z || box.m_min.z > m_max.z)
        {
            return OUTSIDE;
        }
        else if (box.m_min.x < m_min.x || box.m_max.x > m_max.x || box.m_min.y < m_min.y || box.m_max.y > m_max.y || box.m_min.z < m_min.z || box.m_max.z > m_max.z)
        {
            return INTERSECTS;
        }
        else
        {
            return INSIDE;
        }
    }

}