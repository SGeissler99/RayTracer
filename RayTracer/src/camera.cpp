#include "pch.h"
#include "camera.h"

Camera::Camera(Vector3 position, Vector3 direction, float fov)
	: m_Position(position), m_Direction(direction), m_FOV(fov)
{
	
}

Vector3 Camera::GetScreenCenter() const {
	return m_Position + m_FOV * m_Direction;
}

Vector3 Camera::GetPosition() const {
	return m_Position;
}