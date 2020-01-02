#include "..\Public\Camera.h"

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
