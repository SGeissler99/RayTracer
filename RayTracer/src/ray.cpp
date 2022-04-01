#include "pch.h"
#include "ray.h"
#include <limits>

Ray::Ray(const Vector3& origin, const Vector3& direction) 
	: m_Origin(origin), m_Direction(direction)
{
}

int Ray::GetNearestIntersection(std::span<Sphere* const> spheres)  {
	int hit_index = -1;

	for (int i = 0; i < spheres.size(); ++i) {
		if (spheres[i]->IntersectRay(*this)) 
			hit_index = i;
	}

	return hit_index;
}

Vector3 Ray::GetOrigin() const {
	return m_Origin;
}

Vector3 Ray::GetDirection() const {
	return m_Direction;
}

Vector3 Ray::GetIntersectionPoint() const {
	return m_Origin + m_Direction * m_Distance;
}

float Ray::GetDistance() const {
	return m_Distance;
}

Ray& Ray::SetDistance(const float& distance) {
	m_Distance = distance;
	return *this;
}