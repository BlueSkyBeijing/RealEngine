#pragma once
#include "..\..\Frame\Public\Device.h"

#include <dxgi1_6.h>
#include <d3d12.h>
#include <d3d12shader.h>
#include <d3dcompiler.h>

class DX12Device : public IDevice
{
public:
	DX12Device();
	virtual ~DX12Device();

	virtual int Init() override;

	virtual int Draw() override;

private:
	IDXGIFactory2*  IDXGIFactory;
	IDXGIAdapter1* IAdapter;
	ID3D12Device* IDX12Device;
};
