#pragma once

class IMesh
{
public:
	virtual int Load() = 0;
};

class Mesh : public IMesh
{
public:
	virtual int Load() = 0;
protected:
	
};
