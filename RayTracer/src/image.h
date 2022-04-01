#pragma once
#include "vector3.h"

class Image
{
public:
	explicit Image(const Vector3& center);

	Vector3 GetPixelLocation(const float& u, const float& v) const;

private:
	Image();

	Vector3 m_Center;
	Vector3 m_TopRight;
	Vector3 m_TopLeft;
	Vector3 m_BottomRight;
	Vector3 m_TRTL;
	Vector3 m_TRBR;
};