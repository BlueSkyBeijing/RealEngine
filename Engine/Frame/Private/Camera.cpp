#include "..\Public\Camera.h"

Camera::Camera(Eigen::Vector3f position, Eigen::Vector3f direction, Eigen::Vector3f up):
	Position(position),
	Direction(direction),
	Up(up)
{

}

Eigen::Vector3f Camera::GetPosition()
{
	return Position;
}

Eigen::Vector3f Camera::GetDirection()
{
	return Direction;
}

Eigen::Vector3f Camera::GetUp()
{
	return Up;
}

int Camera::Load()
{
	return 0;
}

Eigen::Vector3f Camera::GetRotation()
{
	return Direction;
}
