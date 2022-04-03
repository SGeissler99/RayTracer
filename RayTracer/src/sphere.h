#pragma once
#include "ray.h"

class Ray;

class Sphere
{
public:
	Sphere(Vector3 center, Vector3 color, float radius, float specular, float reflective, float refractive);

	bool IntersectRay(Ray& r) const;
	Vector3 GetNormal(Vector3 intersection_point) const;
	Vector3 GetColor() const;
	bool IsPerfectMirror() const;
	bool IsDiElectric() const;
	float GetSpecular() const;
	float GetReflective() const;
	float GetDiffuse() const;
	float GetRefractive() const;

	const float Epsilon = .0001f;

private:
	struct Material {
		float Specular;
		float Reflective;
		float Diffuse;
		float Refractive;
	};

	Sphere();

	Vector3 m_Center;
	Vector3 m_Color;
	float m_Radius;
	Material m_Material;
};

