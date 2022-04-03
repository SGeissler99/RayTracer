#pragma once
#include "vector3.h"

class Light
{
public:
	Light(Vector3 position, Vector3 color, float intensity);

	float GetIntensity() const;
	Vector3 GetPosition() const;
	Vector3 GetColor() const;

private:
	Light();

	Vector3 m_Position;
	Vector3 m_Color;
	float m_Intensity;
};
