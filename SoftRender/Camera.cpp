#include "Camera.h"

namespace SoftRenderer
{
	Camera::Camera()
	{
		calculateViewMatrix();
	}

	Camera::~Camera()
	{

	}

	void Camera::Look(const vec3 &eye, const vec3 &center, const vec3 &up)
	{
        m_position = eye;
        //构造n
        vec3 temp = center - eye;
        m_n = normalize(temp);

        //构建u
        vec3 u = normalize(up);
        temp = cross(u, m_n);
        m_u = normalize(temp);

        //构建v
        temp = cross(m_n, m_u);
        m_v = normalize(temp);

        calculateViewMatrix();
	}

	void Camera::Move(const vec3 &targetPos)
	{
		m_position = targetPos;
		calculateViewMatrix();
	}

	void Camera::SetPerspective(float fov, float aspect, float near, float far)
	{
		m_projectMatrix = perspective(fov, aspect, near, far);
		m_viewPorjectMatrix = m_projectMatrix * m_viewMatrix;
	}

    bool Camera::IsVisibleInFrustum(const AABB &aabb) const
    {
        return m_frustum.IsInside(aabb) != OUTSIDE;
    }

    void Camera::calculateViewMatrix()
	{
		m_viewMatrix = mat4x4(m_u.x, m_u.y, m_u.z, -dot(m_u, m_position), m_v.x, m_v.y, m_v.z, -dot(m_v, m_position), m_n.x, m_n.y, m_n.z, -dot(m_n, m_position), 0.f, 0.f, 0.f, 1.f);
		m_viewPorjectMatrix = m_projectMatrix * m_viewMatrix;
	}

}