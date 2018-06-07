#ifndef __AABB_H__
#define __AABB_H__

#include "type.h"

typedef unsigned int uint32_t;

namespace SoftRenderer {

    /**
    АќЮЇКа
    */
    class AABB
    {
    public:
        AABB();
        AABB(const vec3 &min, const vec3 &max);
        AABB(const AABB &box);
        AABB(vec3 *vertices, uint32_t count);

        ~AABB();

        void UpdateAABB(vec3 *vertices, uint32_t count);

        void computeDisByDir(const vec3 &dir, vec3 *vertices, uint32_t count, uint32_t &min, uint32_t &max);

        Intersection IsIntersect(const vec3 &point);

        Intersection IsIntersect(const AABB &box);

        vec3 m_min;

        vec3 m_max;
    };

}

#endif