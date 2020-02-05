#pragma once
#include "..\..\Utility\Public\Math.h"
#include "..\Public\SceneObject.h"

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
	Camera(Eigen::Vector3f position, Eigen::Vector3f direction, Eigen::Vector3f up);

	virtual Eigen::Vector3f GetPosition() override;
	virtual Eigen::Vector3f GetDirection() override;
	virtual Eigen::Vector3f GetUp() override;

protected:
	Eigen::Vector3f Position;
	Eigen::Vector3f Direction;
	Eigen::Vector3f Up;
};
