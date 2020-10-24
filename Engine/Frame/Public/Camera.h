#pragma once
#include "..\..\Utility\Public\Math.h"
#include "..\Public\SceneObject.h"

#include <Eigen/Dense>

class ICamera
{
public:
	virtual Eigen::Vector3f GetPosition() = 0;
    virtual void SetPosition(Eigen::Vector3f pos) = 0;
	virtual Eigen::Vector3f GetDirection() = 0;
    virtual void SetDirection(Eigen::Vector3f direction) = 0;
    virtual Eigen::Vector3f GetUp() = 0;
	virtual void Tick(float elapsetime) = 0;
};

class Camera : public ICamera
{
public:
	Camera(Eigen::Vector3f position, Eigen::Vector3f direction, Eigen::Vector3f up);

	virtual Eigen::Vector3f GetPosition() override;
    virtual void SetPosition(Eigen::Vector3f pos) override;
	virtual Eigen::Vector3f GetDirection() override;
    virtual void SetDirection(Eigen::Vector3f direction) override;
	virtual Eigen::Vector3f GetUp() override;
    virtual void Tick(float elapsetime) override;

protected:
	Eigen::Vector3f Position;
	Eigen::Vector3f Direction;
	Eigen::Vector3f Up;
};
