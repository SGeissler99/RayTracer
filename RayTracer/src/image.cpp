#include "pch.h"
#include "image.h"

image::image(vector3 center) 
	: m_Center(center)
{
	m_TopRight = center + vector3(-1.f, -1.f, 0.f);
	m_TopLeft = center + vector3(1.f, -1.f, 0.f);
	m_BottomRight = center + vector3(-1.f, 1.f, 0.f);

	m_TRTL = m_TopRight - m_TopLeft;
	m_TRBR = m_TopRight - m_BottomRight;
}

vector3 image::pixel_location(const float& u, const float& v) const {
	return m_TopRight + u * m_TRTL + v * m_TRBR;
}
