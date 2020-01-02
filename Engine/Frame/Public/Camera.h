#pragma once
#include "..\..\Utility\Public\Math.h"
#include <Eigen/Dense>

class ICamera
{
public:
	virtual Eigen::Vector3f GetPosition() = 0;
	virtual Eigen::Vector3f GetDirection() = 0;
	virtual Eigen::Vector3f GetUp() = 0;
};

class Camera : public ICamera
{
public:
	virtual Eigen::Vector3f GetPosition();
	virtual Eigen::Vector3f GetDirection();
	virtual Eigen::Vector3f GetUp();

protected:
	Eigen::Vector3f Position;
	Eigen::Vector3f Direction;
	Eigen::Vector3f Up;
};
