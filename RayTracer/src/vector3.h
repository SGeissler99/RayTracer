#pragma once

struct vector3
{
	vector3();
	vector3(float a);
	vector3(float a, float b, float c);
	~vector3();

	float x, y, z;

	vector3 operator- () const;
	vector3 operator- (const vector3& other) const;
	vector3& operator-= (const vector3& other);
	vector3& operator-= (const float& scalar);

	vector3& operator+= (const float& scalar);
	vector3 operator+ (const vector3& other) const;
	vector3& operator+= (const vector3& other);

	vector3 operator* (const vector3& other) const;
	vector3& operator*= (const vector3& other);
	vector3& operator*= (const float& scalar);

	vector3 operator/ (const vector3& other) const;
	vector3& operator/= (const vector3& other);
	vector3& operator/= (const float& scalar);

	float operator[] (int index) const;

	static float clamp(const float& value, const float& minVal, const float& maxVal);
	void clamp(const float& minVal, const float& maxVal);
	void clamp(const vector3& minVal, const vector3& maxVal);

	float dot(const vector3& other) const;
	vector3 cross(const vector3& other) const;

	float length() const;
	vector3& normalize();
};

inline vector3 operator* (const float& scalar, const vector3& vec) {
	return vector3(scalar * vec.x, scalar * vec.y, scalar * vec.z);
}

inline vector3 operator+ (const float& scalar, const vector3& vec) {
	return vector3(vec.x + scalar, vec.y + scalar, vec.z + scalar);
}

inline vector3 operator/ (const float& scalar, const vector3& vec) {
	return vector3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
}

inline vector3 operator- (const float& scalar, const vector3& vec) {
	return vector3(vec.x - scalar, vec.y - scalar, vec.z - scalar);
}