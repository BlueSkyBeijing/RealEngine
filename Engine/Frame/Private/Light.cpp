#include "..\Public\Light.h"

Eigen::Vector3f Light::GetColor()
{
	return Color;
}

Eigen::Vector3f DirectonalLight::GetDirection()
{
	return Direction;
}

void DirectonalLight::SetDirection(Eigen::Vector3f newdirection)
{
	Direction = newdirection;
}

Eigen::Vector3f PointLight::GetPosition()
{
	return Position;
}

Eigen::Vector3f SpotLight::GetDirection()
{
	return Direction;
}

Eigen::Vector3f SpotLight::GetPosition()
{
	return Position;
}
