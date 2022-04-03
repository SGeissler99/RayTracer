#pragma once
#include "vector3.h"

class Image
{
public:
	explicit Image(Vector3 center);

	Vector3 GetPixelLocation(float u, float v) const;

private:
	Image();

	Vector3 m_Center;
	Vector3 m_TopRight;
	Vector3 m_TopLeft;
	Vector3 m_BottomRight;
	Vector3 m_TRTL;
	Vector3 m_TRBR;

	const Vector3 TRVector = Vector3(-1, -1, 0);
	const Vector3 TLVector = Vector3(1, -1, 0);
	const Vector3 BRVector = Vector3(-1, 1, 0);
};