#include "pch.h"
#include "vector3.h"

vector3::vector3() 
	: x(0.f), y(0.f), z(0.f) {
}

vector3::vector3(float a) 
	: x(a), y(a), z(a) {
}

vector3::vector3(float a, float b, float c) 
	: x(a), y(b), z(c) {
}

vector3::~vector3() {
	
}

vector3 vector3::operator- () const {
	return vector3(-x, -y, -z);
}

vector3 vector3::operator- (const vector3& other) const {
	return vector3(x - other.x, y - other.y, z - other.z);
}

vector3& vector3::operator-= (const vector3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

vector3& vector3::operator-= (const float& scalar) {
	x -= scalar;
	y -= scalar;
	z -= scalar;

	return *this;
}

vector3& vector3::operator+= (const float& scalar) {
	x += scalar;
	y += scalar;
	z += scalar;

	return *this;
}

vector3 vector3::operator+ (const vector3& other) const {
	return vector3(x + other.x, y + other.y, z + other.z);
}

vector3& vector3::operator+= (const vector3& other) {
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

vector3 vector3::operator* (const vector3& other) const {
	return vector3(x * other.x, y * other.y, z * other.z);
}

vector3& vector3::operator*= (const vector3& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}

vector3& vector3::operator*= (const float& scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

vector3 vector3::operator/ (const vector3& other) const {
	return vector3(x / other.x, y / other.y, z / other.z);
}

vector3& vector3::operator/= (const vector3& other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;

	return *this;
}

vector3& vector3::operator/= (const float& scalar) {
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

float vector3::operator[] (int index) const {
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

float vector3::clamp(const float& value, const float& minVal, const float& maxVal) {
	return max(minVal, min(value, maxVal));
}

void vector3::clamp(const float& minVal, const float& maxVal) {
	x = clamp(x, minVal, maxVal);
	y = clamp(y, minVal, maxVal);
	z = clamp(z, minVal, maxVal);
}

void vector3::clamp(const vector3& minVal, const vector3& maxVal) {
	x = clamp(x, minVal.x, maxVal.x);
	y = clamp(y, minVal.y, maxVal.y);
	z = clamp(z, minVal.z, maxVal.z);
}

float vector3::dot(const vector3& other) const {
	return x * other.x + y * other.y + z * other.z;
}

vector3 vector3::cross(const vector3& other) const {
	return vector3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	);
}

float vector3::length() const {
	return sqrtf(x * x + y * y + z * z);
}

vector3& vector3::normalize() {
	*this /= length();
	return *this;
}