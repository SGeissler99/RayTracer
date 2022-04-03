#pragma once
#include "vector3.h"

class Camera
{
public:
	Camera(Vector3 position, Vector3 direction, float fov);

	Vector3 GetScreenCenter() const;
	Vector3 GetPosition() const;

private:
	Camera();

	Vector3 m_Position;
	Vector3 m_Direction;
	float m_FOV;
};

