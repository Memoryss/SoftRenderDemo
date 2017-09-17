#include "Camera.h"

namespace SoftRenderer
{
	Camera::Camera()
	{
		m_x = vec3(1.f, 0.f, 0.f);
		m_y = vec3(0.f, 1.f, 0.f);
		m_z = vec3(0.f, 0.f, 1.f);

		m_position = vec3(0.f, 0.f, 5.f);

		calculateViewMatrix();
	}

	Camera::~Camera()
	{

	}

	void Camera::Look()
	{
		//TODO
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

	void Camera::calculateViewMatrix()
	{
		m_viewMatrix = mat4x4(m_x.x, m_y.x, m_z.x, 0.f, m_x.y, m_y.y, m_z.y, 0.f, m_x.z, m_y.z, m_z.z, 0.f, -dot(m_x, m_position), -dot(m_z, m_position), -dot(m_z, m_position), 1.f);
		m_viewPorjectMatrix = m_projectMatrix * m_viewMatrix;
	}

}