#ifndef __PLANE_H__
#define __PLANE_H__

#include "type.h"
namespace SoftRenderer {
	/**
	Æ½Ãæ
	*/
	class Plane
	{
	public:
		Plane();

		Plane(const vec3 &p0, const vec3 &p1, const vec3 &p2);
		Plane(const Plane& p);
		Plane(const vec3 &normal, const vec3 &point);

		Plane & operator=(const Plane &plane);

        void SetPoints(const vec3 &p0, const vec3 &p1, const vec3 &p2);

		~Plane();

		float Distance(const vec3 &point);

		vec3 Reflect(const vec3 &dir);

		vec3 Project(const vec3 &point);

		vec3 m_normal;
		float m_distance;
	};

}
#endif