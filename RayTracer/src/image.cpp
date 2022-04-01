#include "pch.h"
#include "image.h"

Image::Image(const Vector3& center) 
	: m_Center(center)
{
	m_TopRight = center + Vector3(-1.f, -1.f, 0.f);
	m_TopLeft = center + Vector3(1.f, -1.f, 0.f);
	m_BottomRight = center + Vector3(-1.f, 1.f, 0.f);

	m_TRTL = m_TopLeft - m_TopRight;
	m_TRBR = m_BottomRight - m_TopRight;
}

Vector3 Image::GetPixelLocation(const float& u, const float& v) const {
	return m_TopRight + u * m_TRTL + v * m_TRBR;
}
