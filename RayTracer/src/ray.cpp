#include "pch.h"
#include "ray.h"
#include <limits>

ray::ray(vector3 origin, vector3 direction) 
	: m_Origin(origin), m_Direction(direction)
{
	Distance = FLT_MAX;
}

int ray::nearest_intersection(const std::vector<sphere*>& spheres) {
	int hit_index = -1;

	for (int i = 0; i < spheres.size(); ++i) {
		if (spheres[i]->intersect_ray(*this)) 
			hit_index = i;
	}

	return hit_index;
}

vector3 ray::get_origin() const {
	return m_Origin;
}

vector3 ray::get_direction() const {
	return m_Direction;
}

vector3 ray::get_intersection() const {
	return m_Origin + m_Direction * Distance;
}