#pragma once
#include "ray.h"

class Ray;

class Sphere
{
public:
	Sphere(const Vector3& center, const float& radius);

	bool IntersectRay(Ray& r) const;
	Vector3 GetNormal(const Vector3& intersection_point) const;

	const float Epsilon = .0001f;

private:
	Sphere();

	Vector3 m_Center;
	float m_Radius;
};

