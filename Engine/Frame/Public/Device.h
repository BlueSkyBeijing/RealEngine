#pragma once

class IDevice
{
public:
	virtual int Init() = 0;
	virtual int UnInit() = 0;
	virtual int Clear() = 0;
	virtual int Draw() = 0;
};

class Device : public IDevice
{
public:
	virtual int Init() override;
	virtual int UnInit() override;
	virtual int Clear() override;
	virtual int Draw() override;
};

