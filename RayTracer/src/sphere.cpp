#include "pch.h"
#include "sphere.h"

sphere::sphere(vector3 center, float radius) 
	: m_Center(center), m_Radius(radius)
{
}

bool sphere::intersect_ray(ray& r) const {
	vector3 c = m_Center - r.get_origin();
	const vector3& ray_direction = r.get_direction();
	float t = c.dot(ray_direction);
	vector3 q = c - t * ray_direction;
	float p2 = q.dot(q);

	if (p2 > m_Radius) 
		return false;

	t -= sqrtf(m_Radius - p2);

	if ((t < r.Distance) && t > epsilon) {
		r.Distance = t;
		return true;
	}

	return false;
}

vector3 sphere::get_normal(const vector3& intersection_point) const {
	return (intersection_point - m_Center).normalize();
}