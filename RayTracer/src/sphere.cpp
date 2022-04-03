#include "pch.h"
#include "sphere.h"

Sphere::Sphere(Vector3 center, Vector3 color, float radius, float specular, float reflective, float refractive)
	: m_Center(center), m_Color(color), m_Radius(radius), m_Material({ specular, reflective, 1 - specular, refractive })
{
}

bool Sphere::IntersectRay(Ray& r) const {
	Vector3 c = m_Center - r.GetOrigin();
	const Vector3& ray_direction = r.GetDirection();
	float t = c.Dot(ray_direction);
	Vector3 q = c - t * ray_direction;
	float p2 = q.Dot(q);

	if (p2 > m_Radius) 
		return false;

	t -= sqrtf(m_Radius - p2);

	if ((t < r.GetDistance()) && t > Epsilon) {
		r.SetDistance(t);
		return true;
	}

	return false;
}

Vector3 Sphere::GetNormal(Vector3 intersection_point) const {
	return (intersection_point - m_Center).Normalize();
}

Vector3 Sphere::GetColor() const {
	return m_Color;
}

bool Sphere::IsPerfectMirror() const {
	return m_Material.Reflective > 0 && m_Material.Refractive == 0 && m_Material.Specular > 0;
}

bool Sphere::IsDiElectric() const {
	return m_Material.Reflective > 0 && m_Material.Refractive >= 1;
}

float Sphere::GetSpecular() const {
	return m_Material.Specular;
}

float Sphere::GetReflective() const {
	return m_Material.Reflective;
}

float Sphere::GetDiffuse() const {
	return m_Material.Diffuse;
}

float Sphere::GetRefractive() const {
	return m_Material.Refractive;
}