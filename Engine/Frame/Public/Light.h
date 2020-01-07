#pragma once
#include "..\..\Utility\Public\Math.h"
#include <Eigen/Dense>

class ILight
{
public:
	virtual Eigen::Vector3f GetPosition() = 0;
	virtual Eigen::Vector3f GetDirection() = 0;
};

class Light : public ILight
{
public:
	virtual Eigen::Vector3f GetPosition() override;
	virtual Eigen::Vector3f GetDirection() override;
protected:
	Eigen::Vector3f Position;
	Eigen::Vector3f Direction;
};
