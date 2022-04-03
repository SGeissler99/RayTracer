#pragma once

struct Vector3
{
	Vector3();
	explicit Vector3(float a);
	Vector3(float a, float b, float c);

	float x;
	float y;
	float z;

	Vector3 operator- () const;
	Vector3& operator-= (const Vector3& other);
	Vector3& operator-= (const float& scalar);

	Vector3& operator+= (const Vector3& other);
	Vector3& operator+= (const float& scalar);

	Vector3& operator*= (const Vector3& other);
	Vector3& operator*= (const float& scalar);

	Vector3& operator/= (const Vector3& other);
	Vector3& operator/= (const float& scalar);

	float operator[] (int index) const;

	static float Clamp(const float& value, const float& minVal, const float& maxVal);
	void Clamp(const float& minVal, const float& maxVal);
	void Clamp(const Vector3& minVal, const Vector3& maxVal);

	float Dot(const Vector3& other) const;
	float AngleBetween(const Vector3& other) const;
	Vector3 Cross(const Vector3& other) const;

	float Length() const;
	float SquaredLength() const;
	Vector3& Normalize();
};

inline Vector3 operator- (const Vector3& first, const Vector3& second) {
	return Vector3(first.x - second.x, first.y - second.y, first.z - second.z);
}

inline Vector3 operator- (const float& scalar, const Vector3& vec) {
	return Vector3(vec.x - scalar, vec.y - scalar, vec.z - scalar);
}

inline Vector3 operator- (const Vector3& vec, const float& scalar) {
	return Vector3(vec.x - scalar, vec.y - scalar, vec.z - scalar);
}

inline Vector3 operator+ (const Vector3& first, const Vector3& second) {
	return Vector3(first.x + second.x, first.y + second.y, first.z + second.z);
}

inline Vector3 operator+ (const float& scalar, const Vector3& vec) {
	return Vector3(vec.x + scalar, vec.y + scalar, vec.z + scalar);
}

inline Vector3 operator+ (const Vector3& vec, const float& scalar) {
	return Vector3(vec.x + scalar, vec.y + scalar, vec.z + scalar);
}

inline Vector3 operator* (const Vector3& first, const Vector3& second) {
	return Vector3(first.x * second.x, first.y * second.y, first.z * second.z);
}

inline Vector3 operator* (const float& scalar, const Vector3& vec) {
	return Vector3(scalar * vec.x, scalar * vec.y, scalar * vec.z);
}

inline Vector3 operator* (const Vector3& vec, const float& scalar) {
	return Vector3(scalar * vec.x, scalar * vec.y, scalar * vec.z);
}

inline Vector3 operator/ (const Vector3& first, const Vector3& second) {
	return Vector3(first.x / second.x, first.y / second.y, first.z / second.z);
}

inline Vector3 operator/ (const float& scalar, const Vector3& vec) {
	return Vector3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
}

inline Vector3 operator/ (const Vector3& vec, const float& scalar) {
	return Vector3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
}

std::ostream& operator<<(std::ostream& stream, const Vector3& other);