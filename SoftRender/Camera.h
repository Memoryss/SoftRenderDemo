#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "type.h"

namespace SoftRenderer
{
    //UVNÏà»ú
	class Camera
	{
	public:
		Camera();
		~Camera();

		void Look(const vec3 &eye, const vec3 &center, const vec3 &up);
		void Move(const vec3 &targetPos);

		void SetPerspective(float fov, float aspect, float near, float far);

	private:
		void calculateViewMatrix();

	public:
        vec3 m_u{ 1.f, 0.f, 0.f };
        vec3 m_v{ 0.f, 1.f, 0.f };
        vec3 m_n{ 0.f, 0.f, 1.f };
        vec3 m_position{ 0.f, 0.f, 5.f };

		mat4x4 m_viewMatrix;
		mat4x4 m_projectMatrix;
		mat4x4 m_viewPorjectMatrix;
	};
}

#endif
