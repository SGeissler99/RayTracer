#include "pch.h"
#include "vector3.h"

Vector3::Vector3() 
	: x(0.f), y(0.f), z(0.f) {
}

Vector3::Vector3(float a) 
	: x(a), y(a), z(a) {
}

Vector3::Vector3(float a, float b, float c) 
	: x(a), y(b), z(c) {
}

Vector3 Vector3::operator- () const {
	return Vector3(-x, -y, -z);
}

Vector3& Vector3::operator-= (const Vector3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Vector3& Vector3::operator-= (const float& scalar) {
	x -= scalar;
	y -= scalar;
	z -= scalar;

	return *this;
}

Vector3& Vector3::operator+= (const float& scalar) {
	x += scalar;
	y += scalar;
	z += scalar;

	return *this;
}

Vector3& Vector3::operator+= (const Vector3& other) {
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vector3& Vector3::operator*= (const Vector3& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}

Vector3& Vector3::operator*= (const float& scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

Vector3& Vector3::operator/= (const Vector3& other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;

	return *this;
}

Vector3& Vector3::operator/= (const float& scalar) {
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

float Vector3::operator[] (int index) const {
	switch (index) {
	case 0:
		return x;
	case 1:
		return y;
	case 2: 
		return z;
	default:
		return 0;
	}
}

float Vector3::Clamp(const float& value, const float& minVal, const float& maxVal) {
	return max(minVal, min(value, maxVal));
}

void Vector3::Clamp(const float& minVal, const float& maxVal) {
	x = Clamp(x, minVal, maxVal);
	y = Clamp(y, minVal, maxVal);
	z = Clamp(z, minVal, maxVal);
}

void Vector3::Clamp(const Vector3& minVal, const Vector3& maxVal) {
	x = Clamp(x, minVal.x, maxVal.x);
	y = Clamp(y, minVal.y, maxVal.y);
	z = Clamp(z, minVal.z, maxVal.z);
}

float Vector3::Dot(const Vector3& other) const {
	return x * other.x + y * other.y + z * other.z;
}

float Vector3::AngleBetween(const Vector3& other) const {
	return acosf(Dot(other) / (Length() * other.Length()));
}

Vector3 Vector3::Cross(const Vector3& other) const {
	return Vector3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	);
}

float Vector3::Length() const {
	return sqrtf(x * x + y * y + z * z);
}

float Vector3::SquaredLength() const {
	return x * x + y * y + z * z;
}

Vector3& Vector3::Normalize() {
	*this /= Length();
	return *this;
}