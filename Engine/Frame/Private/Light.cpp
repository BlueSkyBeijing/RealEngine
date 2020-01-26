#include "..\Public\Light.h"

const Eigen::Vector3f& Light::GetColor() const
{
	return Color;
}

const Eigen::Vector3f& DirectonalLight::GetDirection() const
{
	return Direction;
}

void DirectonalLight::SetDirection(Eigen::Vector3f newdirection)
{
	Direction = newdirection;
}

const Eigen::Vector3f& PointLight::GetPosition() const
{
	return Position;
}

const Eigen::Vector3f& SpotLight::GetDirection() const
{
	return Direction;
}

const Eigen::Vector3f& SpotLight::GetPosition() const
{
	return Position;
}
