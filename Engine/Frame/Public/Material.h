#pragma once
#include <Eigen/Dense>

class IMaterial
{
public:
	virtual int Load() = 0;
};

class Material : public IMaterial
{
public:
	virtual int Load() = 0;
protected:
	Eigen::Vector3f BaseColor;
	float Metallic;
	float Roughness;
	Eigen::Vector3f Emissive;
};

