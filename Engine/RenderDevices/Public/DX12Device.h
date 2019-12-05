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
	ID3D12CommandQueue* IDX12CommandQueue;
	ID3D12CommandAllocator* IDX12CommandAllocator;
	ID3D12GraphicsCommandList* IDX12CommandList;
	IDXGISwapChain1* IDXGISwapChain;
	ID3D12RootSignature* IDX12RootSignature;
	ID3D12PipelineState* IDX12PipleLineState;
	ID3D12Fence* IDX12Fence;
	ID3D12DescriptorHeap* IDX12DescriptorHeap;
	ID3D12Resource* IRenderTargets[2];
};
