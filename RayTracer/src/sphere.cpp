#include "pch.h"
#include "sphere.h"

Sphere::Sphere(const Vector3& center, const float& radius) 
	: m_Center(center), m_Radius(radius)
{
}

bool Sphere::IntersectRay(Ray& r) const {
	Vector3 c = m_Center - r.GetOrigin();
	const Vector3& ray_direction = r.GetDirection();
	float t = c.Dot(ray_direction);
	Vector3 q = c - t * ray_direction;
	float p2 = q.Dot(q);

	if (p2 > m_Radius) 
		return false;

	t -= sqrtf(m_Radius - p2);

	if ((t < r.GetDistance()) && t > Epsilon) {
		r.SetDistance(t);
		return true;
	}

	return false;
}

Vector3 Sphere::GetNormal(const Vector3& intersection_point) const {
	return (intersection_point - m_Center).Normalize();
}