#pragma once
#include "pch.h"
#include "vector3.h"

namespace vector_math {
	vector3 clamp(const vector3& vec, const float& minVal, const float& maxVal)
	{
		return vector3(
			vector3::clamp(vec.x, minVal, maxVal),
			vector3::clamp(vec.y, minVal, maxVal),
			vector3::clamp(vec.z, minVal, maxVal)
		);
	}

	vector3 clamp(const vector3& vec, const vector3& minVal, const vector3& maxVal) {
		return vector3(
			vector3::clamp(vec.x, minVal.x, maxVal.x),
			vector3::clamp(vec.y, minVal.y, maxVal.y),
			vector3::clamp(vec.z, minVal.z, maxVal.z)
		);
	}

	float dot(const vector3& first, const vector3& second) {
		return first.x * second.x + first.y * second.y + first.z * second.z;
	}

	vector3 cross(const vector3& first, const vector3& second) {
		return vector3(
			first.y * second.z - first.z * second.y,
			first.z * second.x - first.x * second.z,
			first.x * second.y - first.y * second.x
		);
	}

	vector3 reflect(const vector3& incoming, const vector3& normal) {		
		return incoming - 2.f * normal * normal.dot(incoming);
	}

	vector3 normalized(const vector3& vec) {
		return vec / vec.length();
	}
}
