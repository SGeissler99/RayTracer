#pragma once
#include "vector3.h"

class image
{
public:
	image(vector3 center);

	vector3 pixel_location(const float& u, const float& v) const;

private:
	image();

	vector3 m_Center, m_TopRight, m_TopLeft, m_BottomRight, m_TRTL, m_TRBR;
};