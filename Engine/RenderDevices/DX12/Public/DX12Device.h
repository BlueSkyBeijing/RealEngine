#pragma once
#include "..\..\..\Frame\Public\Device.h"
#include "..\..\..\Frame\Public\Device.h"
#include "d3dx12.h"

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

protected:
	ID3D12Resource* GetBackBuffer() const;
	D3D12_CPU_DESCRIPTOR_HANDLE GetBackBufferView() const;
	D3D12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView() const;

private:
	IDXGIFactory2*  IDXGIFactory;
	IDXGIAdapter1* IAdapter;
	ID3D12Device* IDX12Device;
	ID3D12CommandQueue* IDX12CommandQueue;
	ID3D12CommandAllocator* IDX12CommandAllocator;
	ID3D12GraphicsCommandList* IDX12CommandList;
	IDXGISwapChain* IDXGISwapChain;
	ID3D12RootSignature* IDX12RootSignature;
	ID3D12PipelineState* IDX12PipleLineState;
	ID3D12Fence* IDX12Fence;
	ID3D12DescriptorHeap* IDX12DescriptorHeapRenderTarget;
	ID3D12DescriptorHeap* IDX12DescriptorHeapDepthStencil;
	ID3D12Resource* IRenderTargets[2];
	HANDLE EventHandle;
	UINT64 FenceValue;
	ID3DBlob* VertexShader;
	ID3DBlob *PixelShader;
	ID3D12Resource* VertexBuffer;
	D3D12_VIEWPORT ViewPort;
	D3D12_RECT ScissorRect;
	D3D12_VERTEX_BUFFER_VIEW VertexBufferView;
	UINT FrameIndex;
	UINT RTVDescriptorSize;
	UINT DSVDescriptorSize;
};
