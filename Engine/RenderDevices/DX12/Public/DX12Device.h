#pragma once
#include "..\..\..\Frame\Public\Device.h"
#include "..\..\..\Frame\Public\Device.h"
#include "d3dx12.h"
#include "DX12Utility.h"

#include <dxgi1_6.h>
#include <d3d12.h>
#include <d3d12shader.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include <assert.h>
#include <atlstr.h >
#include <comdef.h>
#include <fstream>
#include <array>

using namespace DirectX;

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
	ID3D12DescriptorHeap* ConstantBufferHeap;
	ID3D12Resource* IRenderTargets[2];
	ID3D12Resource* DepthStencilBuffer;
	HANDLE EventHandle;
	UINT64 FenceValue;
	ID3DBlob* VertexShader;
	ID3DBlob *PixelShader;
	ID3D12Resource* VertexBuffer;
	ID3D12Resource* IndexBuffer;
	ID3D12Resource* ConstantBuffer;
	D3D12_VIEWPORT ViewPort;
	D3D12_RECT ScissorRect;
	D3D12_VERTEX_BUFFER_VIEW VertexBufferView;
	D3D12_INDEX_BUFFER_VIEW IndexBufferView;
	UINT ChainBufferndex;
	UINT SwapChainBufferCount;
	UINT RTVDescriptorSize;
	UINT DSVDescriptorSize;
	XMFLOAT4X4 WorldMatrix;
	XMFLOAT4X4 ViewMatrix;
	XMFLOAT4X4 ProjMatrix;
	UINT IndexCount;
	DXGI_FORMAT BackBufferFormat;
	DXGI_FORMAT DepthStencilFormat;
};
