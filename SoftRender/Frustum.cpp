#include "Frustum.h"

#include <algorithm>

namespace SoftRenderer {

	Frustum::Frustum()
	{
	}

	Frustum::Frustum(const Frustum & frustum)
	{
		*this = frustum;
	}

	Frustum & Frustum::operator=(const Frustum & frustum)
	{
		
		for (uint32_t i = 0; i < FRUSTUM_NUM_PLANES; ++i)
		{
			m_planes[i] = frustum.m_planes[i];
		}
		for (uint32_t i = 0; i < FRUSTUM_NUM_VECTICES; ++i)
		{
			m_vertices[i] = frustum.m_vertices[i];
		}

		return *this;
	}

	void Frustum::SetFrustum(float fov, float aspectRatio, float nearZ, float farZ, const mat4x4 &transform)
	{
		nearZ = std::max(nearZ, 0.f);
		farZ = std::max(farZ, nearZ);

        float halfFovTan = tanf(fov * M_DEGTORAD / 2);

        vec3 near, far;
        near.z = nearZ;
        near.y = near.z * halfFovTan;
        near.x = near.y * aspectRatio;

        far.z = farZ;
        far.y = far.z * halfFovTan;
        far.x = far.y * aspectRatio;

        UpdateVertices(near, far, transform);
	}

	Intersection Frustum::IsInside(const vec3 & point) const
	{
		return OUTSIDE;
	}

	Intersection Frustum::IsInside(const AABB & box) const
	{
		return OUTSIDE;
	}

	void Frustum::UpdatePlanes()
	{
        m_planes[PLANE_NEAR].SetPoints(m_vertices[2], m_vertices[1], m_vertices[0]);
        m_planes[PLANE_LEFT].SetPoints(m_vertices[3], m_vertices[7], m_vertices[6]);
        m_planes[PLANE_RIGHT].SetPoints(m_vertices[1], m_vertices[5], m_vertices[4]);
        m_planes[PLANE_UP].SetPoints(m_vertices[0], m_vertices[4], m_vertices[7]);
        m_planes[PLANE_DOWN].SetPoints(m_vertices[6], m_vertices[5], m_vertices[4]);
        m_planes[PLANE_FAR].SetPoints(m_vertices[5], m_vertices[6], m_vertices[7]);
	}

    void Frustum::UpdateVertices(const vec3 & near, const vec3 & far, const mat4x4 & transform)
    {
        m_vertices[0] = transform * near;
        m_vertices[1] = transform * vec3(near.x, -near.y, near.z);
        m_vertices[2] = transform * vec3(-near.x, -near.y, near.z);
        m_vertices[3] = transform * vec3(-near.x, near.y, near.z);
        m_vertices[4] = transform * far;
        m_vertices[5] = transform * vec3(far.x, -far.y, far.z);
        m_vertices[6] = transform * vec3(-far.x, -far.y, far.z);
        m_vertices[7] = transform * vec3(-far.x, far.y, far.z);

        UpdatePlanes();
    }



}
