#pragma once
#include "vector3.h"

class camera
{
public:
	camera(const vector3&, const vector3&, const float&);
	
	~camera();

	vector3 get_screen_center() const;
	vector3 get_position() const;

private:
	camera();

	vector3 m_Position, m_Direction;
	float m_FOV;
};

