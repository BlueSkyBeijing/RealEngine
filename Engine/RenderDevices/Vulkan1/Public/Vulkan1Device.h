#pragma once
#include "..\..\..\Frame\Public\Device.h"
#include "Vulkan1Utility.h"

class Vulkan1Device : public IDevice
{
public:
	Vulkan1Device();
	virtual ~Vulkan1Device();

	virtual int Init() override;

	virtual int Draw() override;

protected:

private:
};
