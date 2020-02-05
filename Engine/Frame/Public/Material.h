#pragma once
#include <Eigen/Dense>

class IMaterial
{
public:
	virtual int Load() = 0;
	virtual void createConstants() = 0;

};

class Material : public IMaterial
{
public:
	virtual int Load() override;
	virtual void createConstants() override;
protected:
	Eigen::Vector3f BaseColor;
	Eigen::Vector3f Emissive;
	float Specular;
	float Metallic;
	float Roughness;
};

