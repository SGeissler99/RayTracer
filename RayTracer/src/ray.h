#pragma once
#include "vector3.h"
#include "sphere.h"

class sphere;

class ray
{
public:
	ray(vector3 origin, vector3 direction);
	int nearest_intersection(const std::vector<sphere*>& spheres);

	vector3 get_origin() const;
	vector3 get_direction() const;

	float Distance;

private:
	ray();

	vector3 m_Origin, m_Direction;
};
