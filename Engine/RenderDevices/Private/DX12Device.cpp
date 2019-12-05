#include "..\Public\DX12Device.h"
#include "..\..\Frame\Public\RenderTarget.h"
#include "..\..\Platforms\Windows\Public\EngineWindows.h"
#include "..\..\Platforms\Windows\Public\RenderWindowWindows.h"

#include <assert.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")

DX12Device::DX12Device()
{

}

DX12Device::~DX12Device()
{

}

int DX12Device::Init()
{
	// Create DXGI factory
	CreateDXGIFactory2(0, IID_PPV_ARGS(&IDXGIFactory));

	// Create DX12 device
	for (UINT AdapterIndex = 1; DXGI_ERROR_NOT_FOUND != IDXGIFactory->EnumAdapters1(AdapterIndex, &IAdapter); ++AdapterIndex)
	{
		DXGI_ADAPTER_DESC1 Desc = {};
		IAdapter->GetDesc1(&Desc);

		if (Desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			continue;
		}
		if (SUCCEEDED(D3D12CreateDevice(IAdapter, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&IDX12Device))))
		{
			break;
		}
	}

	// Create command queue
	D3D12_COMMAND_QUEUE_DESC QueueDesc = {};
	QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	IDX12Device->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&IDX12CommandQueue));

	// Create swipe chain
	IRenderTarget* RenderTarget = EngineWindows::GetInstance()->GetRenderTarget();
	assert(RenderTarget != nullptr);
	DXGI_SWAP_CHAIN_DESC1 SwapChainDesc = {};
	SwapChainDesc.BufferCount = 2;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapChainDesc.SampleDesc.Count = 1;

	HWND WindowHandle = nullptr;
	RenderWindowWindows *RenderWindow = dynamic_cast<RenderWindowWindows*>(EngineWindows::GetInstance()->GetRenderTarget());
	if (nullptr != RenderWindow)
	{
		WindowHandle = RenderWindow->GetRenderWindowHandle();
	}
	assert(WindowHandle != nullptr);
	IDXGIFactory->CreateSwapChainForHwnd(IDX12Device, WindowHandle, &SwapChainDesc, nullptr, nullptr, &IDXGISwapChain);

	// Create render view description
	D3D12_DESCRIPTOR_HEAP_DESC DescriptorHeapDesc = {};
	DescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	DescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	DescriptorHeapDesc.NumDescriptors = 2;
	IDX12Device->CreateDescriptorHeap(&DescriptorHeapDesc, IID_PPV_ARGS(&IDX12DescriptorHeap));

	// Create render view
	int RTVDescriptorSize = IDX12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHandle(IDX12DescriptorHeap->GetCPUDescriptorHandleForHeapStart());
	IDX12Device->CreateRenderTargetView(IRenderTargets[0], nullptr, DescriptorHandle);
	IDX12Device->CreateRenderTargetView(IRenderTargets[1], nullptr, DescriptorHandle);

	// Create root signature
	D3D12_ROOT_SIGNATURE_DESC RootSignatureDesc;
	ID3DBlob* Signature;
	ID3DBlob* Error;
	D3D12SerializeRootSignature(&RootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &Signature, &Error);
	IDX12Device->CreateRootSignature(0, Signature->GetBufferPointer(), Signature->GetBufferSize(), IID_PPV_ARGS(&IDX12RootSignature));

	// Create graphic pipeline state 
	D3D12_GRAPHICS_PIPELINE_STATE_DESC PSODesc = {};
	PSODesc.pRootSignature = IDX12RootSignature;
	PSODesc.DepthStencilState.DepthEnable = FALSE;
	PSODesc.DepthStencilState.StencilEnable = FALSE;
	PSODesc.SampleMask = UINT_MAX;
	PSODesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	PSODesc.NumRenderTargets = 1;
	PSODesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	PSODesc.SampleDesc.Count = 1;

	IDX12Device->CreateGraphicsPipelineState(&PSODesc, IID_PPV_ARGS(&IDX12PipleLineState));

	// Create command allocator
	IDX12Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&IDX12CommandAllocator));

	// Create command list
	IDX12Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, IDX12CommandAllocator, IDX12PipleLineState, IID_PPV_ARGS(&IDX12CommandList));

	// Crete fence
	IDX12Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&IDX12Fence));

	return 0;
}

int DX12Device::Draw()
{
	// Reset command list
	IDX12CommandList->Reset(IDX12CommandAllocator, IDX12PipleLineState);

	// Clear color and depth stencil
	IDX12CommandList->ClearRenderTargetView();
	IDX12CommandList->ClearDepthStencilView();

	// Set render target
	IDX12CommandList->OMSetRenderTargets();

	// Draw
	IDX12CommandList->DrawIndexedInstanced(0, 1, 0, 0, 0);

	// Close command
	IDX12CommandList->Close();

	// Execute command list
	ID3D12CommandList* CommandLists[] = { IDX12CommandList };
	IDX12CommandQueue->ExecuteCommandLists(1, &CommandLists);

	// Present
	IDXGISwapChain->Present(0, 0);

	return 0;
}
