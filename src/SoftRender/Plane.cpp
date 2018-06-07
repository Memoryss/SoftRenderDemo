#include "Plane.h"

namespace SoftRenderer {

	Plane::Plane() : m_distance(0.f)
	{

	}

	Plane::Plane(const vec3 & p0, const vec3 & p1, const vec3 & p2)
	{
        SetPoints(p0, p1, p2);
	}

	Plane::Plane(const Plane & p) : m_normal(p.m_normal), m_distance(p.m_distance)
	{
		
	}

	Plane::Plane(const vec3 & normal, const vec3 & point)
	{
		m_normal = normalize(normal);
		m_distance = -dot(m_normal, point);
	}

	Plane & Plane::operator=(const Plane & plane)
	{
		m_normal = plane.m_normal;
		m_distance = plane.m_distance;
		return *this;
	}

    void Plane::SetPoints(const vec3 & p0, const vec3 & p1, const vec3 & p2)
    {
        vec3 dist1 = p1 - p0;
        vec3 dist2 = p2 - p0;
        m_normal = normalize(cross(dist1, dist2));
        m_distance = -dot(m_normal, p0);
    }

	Plane::~Plane()
	{
	}

	float Plane::Distance(const vec3 & point)
	{
		return dot(m_normal, point) + m_distance;
	}

	vec3 Plane::Reflect(const vec3 & dir)
	{
		return dir - 2.f * dot(m_normal, dir) * m_normal;
	}

	vec3 Plane::Project(const vec3 & point)
	{
		return point - m_normal * (m_distance + dot(m_normal, point));
	}

}