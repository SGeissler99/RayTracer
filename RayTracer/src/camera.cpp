#include "pch.h"
#include "camera.h"

camera::camera(const vector3& position, const vector3& direction, const float& fov)
	: m_Position(position), m_Direction(direction), m_FOV(fov)
{

}

camera::~camera() {

}

vector3 camera::get_screen_center() const {
	return m_Position + m_FOV * m_Direction;
}

vector3 camera::get_position() const {
	return m_Position;
}