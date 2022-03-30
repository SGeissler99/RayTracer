#include "pch.h"
#include "light.h"

light::light(vector3 position, vector3 color, float intensity)
	: m_Position(position), m_Color(color), m_Intensity(intensity)
{

}

float light::get_intensity() const {
	return m_Intensity;
}

vector3 light::get_position() const {
	return m_Position;
}

vector3 light::get_color() const {
	return m_Color;
}