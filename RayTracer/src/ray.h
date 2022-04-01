#pragma once
#include "vector3.h"
#include "sphere.h"

class Sphere;

class Ray
{
public:
	Ray(const Vector3& origin, const Vector3& direction);
	int GetNearestIntersection(std::span<Sphere* const> spheres);

	Vector3 GetOrigin() const;
	Vector3 GetDirection() const;
	Vector3 GetIntersectionPoint() const;
	float GetDistance() const;
	Ray& SetDistance(const float& distance);

private:
	Ray();

	Vector3 m_Origin;
	Vector3 m_Direction;
	float m_Distance = FLT_MAX;
};
