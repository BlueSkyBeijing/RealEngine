#include "..\Public\Light.h"

const Eigen::Vector3f& Light::GetColor() const
{
	return Color;
}

void Light::SetColor(Eigen::Vector3f newcolor)
{
	newcolor.normalize();
	Color = newcolor;
}

const Eigen::Vector3f& DirectonalLight::GetDirection() const
{
	return Direction;
}

void DirectonalLight::SetDirection(Eigen::Vector3f newdirection)
{
	newdirection.normalize();
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
