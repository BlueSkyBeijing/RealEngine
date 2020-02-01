#pragma once
#include "..\..\Utility\Public\Math.h"
#include <Eigen/Dense>

class ILight
{
public:
	virtual const Eigen::Vector3f& GetColor() const = 0;
};

class Light : public ILight
{
public:
	virtual const Eigen::Vector3f& GetColor() const override;
protected:
	Eigen::Vector3f Color;
};

class DirectonalLight : public Light
{
public:
	const Eigen::Vector3f& GetDirection() const;
	void SetDirection(Eigen::Vector3f newdirection);

protected:
	Eigen::Vector3f Direction;
};

class PointLight : public Light
{
public:
	const Eigen::Vector3f& GetPosition() const;

protected:
	Eigen::Vector3f Position;
};

class SpotLight : public Light
{
public:
	const Eigen::Vector3f& GetPosition() const;
	const Eigen::Vector3f& GetDirection() const;

protected:
	Eigen::Vector3f Position;
	Eigen::Vector3f Direction;
};
