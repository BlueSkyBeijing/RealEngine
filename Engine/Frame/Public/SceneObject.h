#pragma once
#include <Eigen/Dense>

class IDevice;

class IRenderable
{
public:
	virtual void CreateConstants(IDevice* device) = 0;
};

class Renderable : public IRenderable
{
public:
	virtual void CreateConstants(IDevice* device) override;
};


class ISceneObject
{
public:
	virtual int Load() = 0;
	virtual Eigen::Vector3f GetPosition() = 0;
	virtual Eigen::Vector3f GetRotation() = 0;
};

class SceneObject : public ISceneObject
{
public:
	virtual int Load() override;
	virtual Eigen::Vector3f GetPosition() override;
	virtual Eigen::Vector3f GetRotation() override;
protected:
	Eigen::Vector3f Position;
	Eigen::Vector3f Rotation;
};
