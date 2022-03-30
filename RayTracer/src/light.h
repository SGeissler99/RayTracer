#pragma once
#include "vector3.h"

class light
{
public:
	light(vector3 position, vector3 color, float intensity);

	float get_intensity() const;
	vector3 get_position() const;
	vector3 get_color() const;

private:
	light();

	vector3 m_Position, m_Color;
	float m_Intensity;
};
