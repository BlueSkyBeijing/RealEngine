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

class Camera : public ICamera, ISceneObject
{
public:
	Camera(Eigen::Vector3f position, Eigen::Vector3f direction, Eigen::Vector3f up);

	virtual Eigen::Vector3f GetPosition();
	virtual Eigen::Vector3f GetDirection();
	virtual Eigen::Vector3f GetUp();

	virtual int Load();
	virtual Eigen::Vector3f GetRotation();

protected:
	Eigen::Vector3f Position;
	Eigen::Vector3f Direction;
	Eigen::Vector3f Up;
};
