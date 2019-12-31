#pragma once
#include "..\..\..\Frame\Public\Device.h"
#include "Vulkan1Utility.h"
#include <vulkan/vulkan.h>

class Vulkan1Device : public IDevice
{
public:
	Vulkan1Device();
	virtual ~Vulkan1Device();

	virtual int Init() override;
	virtual int UnInit() override;

	virtual int Draw() override;

protected:

private:
};
