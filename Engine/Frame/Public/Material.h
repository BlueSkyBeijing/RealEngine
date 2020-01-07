#pragma once

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

};

