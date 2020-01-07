#include "..\Public\Light.h"

Eigen::Vector3f Light::GetPosition()
{
	return Position;
}

Eigen::Vector3f Light::GetDirection()
{
	return Direction;
}
