#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "type.h"

namespace SoftRenderer
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void Look();
		void Move(const vec3 &targetPos);

		void SetPerspective(float fov, float aspect, float near, float far);

	private:
		void calculateViewMatrix();

	public:
		vec3 m_x;
		vec3 m_y;
		vec3 m_z;
		vec3 m_position;

		mat4x4 m_viewMatrix;
		mat4x4 m_projectMatrix;
		mat4x4 m_viewPorjectMatrix;
	};
}

#endif
