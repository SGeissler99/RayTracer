#include "pch.h"
#include "light.h"

Light::Light(Vector3 position, Vector3 color, float intensity)
	: m_Position(position), m_Color(color), m_Intensity(intensity)
{

}

float Light::GetIntensity() const {
	return m_Intensity;
}

Vector3 Light::GetPosition() const {
	return m_Position;
}

Vector3 Light::GetColor() const {
	return m_Color;
}