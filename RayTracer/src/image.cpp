#include "pch.h"
#include "image.h"

Image::Image(Vector3 center) 
	: m_Center(center)
{
	m_TopRight = center + TRVector;
	m_TopLeft = center + TLVector;
	m_BottomRight = center + BRVector;

	m_TRTL = m_TopLeft - m_TopRight;
	m_TRBR = m_BottomRight - m_TopRight;
}

Vector3 Image::GetPixelLocation(float u, float v) const {
	return m_TopRight + u * m_TRTL + v * m_TRBR;
}
