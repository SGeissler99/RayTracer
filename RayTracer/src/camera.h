#pragma once
#include "vector3.h"

class Camera
{
public:
	Camera(const Vector3& position, const Vector3& direction, const float& fov);

	Vector3 GetScreenCenter() const;
	Vector3 GetPosition() const;

private:
	Camera();

	Vector3 m_Position;
	Vector3 m_Direction;
	float m_FOV;
};

