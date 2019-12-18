#pragma once
#include "..\..\Utility\Public\Math.h"
#include <Eigen/Dense>

class ILight
{
public:
	virtual Eigen::Vector3f GetPosition() = 0;
	virtual Eigen::Vector3f GetDirection() = 0;
};

