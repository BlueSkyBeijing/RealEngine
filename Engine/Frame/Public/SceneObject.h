#pragma once
#include <Eigen/Dense>

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
	virtual int Load();
	virtual Eigen::Vector3f GetPosition() override;
	virtual Eigen::Vector3f GetRotation() override;
protected:
	Eigen::Vector3f Position;
	Eigen::Vector3f Rotation;
};
