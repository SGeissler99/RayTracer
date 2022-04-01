#pragma once
#include "pch.h"
#include "vector3.h"

namespace vector_math {
	Vector3 Clamp(const Vector3& vec, const float& minVal, const float& maxVal)
	{
		return Vector3(
			Vector3::Clamp(vec.x, minVal, maxVal),
			Vector3::Clamp(vec.y, minVal, maxVal),
			Vector3::Clamp(vec.z, minVal, maxVal)
		);
	}

	Vector3 Clamp(const Vector3& vec, const Vector3& minVal, const Vector3& maxVal) {
		return Vector3(
			Vector3::Clamp(vec.x, minVal.x, maxVal.x),
			Vector3::Clamp(vec.y, minVal.y, maxVal.y),
			Vector3::Clamp(vec.z, minVal.z, maxVal.z)
		);
	}

	float Dot(const Vector3& first, const Vector3& second) {
		return first.x * second.x + first.y * second.y + first.z * second.z;
	}

	Vector3 Cross(const Vector3& first, const Vector3& second) {
		return Vector3(
			first.y * second.z - first.z * second.y,
			first.z * second.x - first.x * second.z,
			first.x * second.y - first.y * second.x
		);
	}

	Vector3 Reflect(const Vector3& incoming, const Vector3& normal) {		
		return incoming - 2.f * normal * normal.Dot(incoming);
	}

	Vector3 Normalized(const Vector3& vec) {
		return vec / vec.Length();
	}

	float AngleBetween(const Vector3& first, const Vector3& second) {
		return acosf(Dot(first, second) / (first.Length() * second.Length()));
	}

	float Length(const Vector3& vec) {
		return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	float SquaredLength(const Vector3& vec) {
		return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	}
}
