#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__

#include "Plane.h"
#include "type.h"

namespace SoftRenderer {

	class AABB;

	enum FrustumPlane
	{
		PLANE_NEAR = 0,
		PLANE_FAR,
		PLANE_LEFT,
		PLANE_RIGHT,
		PLANE_UP,
		PLANE_DOWN,
	};

	static const uint32_t FRUSTUM_NUM_PLANES = 6;
	static const uint32_t FRUSTUM_NUM_VECTICES = 8;

	/**
	ÊÓ×¶Ìå
	*/
	class Frustum
	{
	public:
		Frustum();
		Frustum(const Frustum &frustum);

		Frustum & operator=(const Frustum &frustum);

		void SetFrustum(float fov, float aspectRatio, float nearZ, float farZ, const mat4x4 &transform);

		Intersection IsInside(const vec3 &point) const;

		Intersection IsInside(const AABB &box) const;

		void UpdatePlanes();

        void UpdateVertices(const vec3 &near, const vec3 &far, const mat4x4 &transform);

		Plane m_planes[FRUSTUM_NUM_PLANES];
		vec3 m_vertices[FRUSTUM_NUM_VECTICES];
	};

}

#endif