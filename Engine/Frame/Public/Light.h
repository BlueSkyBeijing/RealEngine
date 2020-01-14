#pragma once
#include "..\..\Utility\Public\Math.h"
#include <Eigen/Dense>

class ILight
{
public:
	virtual Eigen::Vector3f GetColor() = 0;
};

class Light : public ILight
{
public:
	virtual Eigen::Vector3f GetColor() override;
protected:
	Eigen::Vector3f Color;
};

class DirectonalLight : public Light
{
public:
	Eigen::Vector3f GetDirection();
	void SetDirection(Eigen::Vector3f newdirection);

protected:
	Eigen::Vector3f Direction;
};

class PointLight : public Light
{
public:
	Eigen::Vector3f GetPosition();

protected:
	Eigen::Vector3f Position;
};

class SpotLight : public Light
{
public:
	Eigen::Vector3f GetPosition();
	Eigen::Vector3f GetDirection();

protected:
	Eigen::Vector3f Position;
	Eigen::Vector3f Direction;
};
