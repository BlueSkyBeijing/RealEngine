#pragma once
#include "..\..\Frame\Public\Device.h"

class DX12Device : public IDevice
{
public:
	DX12Device();
	virtual ~DX12Device();

	virtual int Draw() override;
};
