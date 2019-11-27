#pragma once

class IDevice
{
public:
	virtual int Draw() = 0;
};


class DX12Device : public IDevice
{
public:
	DX12Device();
	virtual ~DX12Device();

	virtual int Draw() override;
};
