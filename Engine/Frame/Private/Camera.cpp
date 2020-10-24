#include "..\Public\Camera.h"

Camera::Camera(Eigen::Vector3f position, Eigen::Vector3f direction, Eigen::Vector3f up):
	Position(position),
	Direction(direction),
	Up(up)
{
	Direction.normalize();
	Up.normalize();
}

Eigen::Vector3f Camera::GetPosition()
{
	return Position;
}

void Camera::SetPosition(Eigen::Vector3f pos)
{
	Position = pos;
}

Eigen::Vector3f Camera::GetDirection()
{
	return Direction;
}

void Camera::SetDirection(Eigen::Vector3f direction)
{
	Direction = direction;
}

Eigen::Vector3f Camera::GetUp()
{
	return Up;
}

void Camera::Tick(float elapsetime)
{

}
