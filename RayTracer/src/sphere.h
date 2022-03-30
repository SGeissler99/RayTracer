#pragma once
#include "ray.h"

class ray;

class sphere
{
public:
	sphere(vector3 center, float radius);

	bool intersect_ray(ray& r) const;
	vector3 get_normal(const vector3& intersection_point) const;


	const float Epsilon = .0001f;

private:
	sphere();

	vector3 m_Center;
	float m_Radius;
};

