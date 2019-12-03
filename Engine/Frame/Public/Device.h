#pragma once

class IDevice
{
public:
	virtual int Init() = 0;
	virtual int Draw() = 0;
};

