#include "..\Public\DX12Device.h"
#include "..\..\..\Frame\Public\RenderTarget.h"
#include "..\..\..\Platforms\Windows\Public\EngineWindows.h"
#include "..\..\..\Platforms\Windows\Public\RenderWindowWindows.h"

#include <assert.h>
#include <atlstr.h >
#include <comdef.h>
#include <fstream>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")

struct VERTEX 
{ 
	FLOAT X, Y, Z; 
	FLOAT Color[4]; 
};

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
	for (UINT AdapterIndex = 0; DXGI_ERROR_NOT_FOUND != IDXGIFactory->EnumAdapters1(AdapterIndex, &IAdapter); ++AdapterIndex)
	{
		DXGI_ADAPTER_DESC1 Desc = {};
		IAdapter->GetDesc1(&Desc);

		if (Desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			continue;
		}
		HRESULT Result = D3D12CreateDevice(IAdapter, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&IDX12Device));
		if (SUCCEEDED(Result))
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

	HWND WindowHandle = nullptr;
	RenderWindowWindows *RenderWindow = dynamic_cast<RenderWindowWindows*>(EngineWindows::GetInstance()->GetRenderTarget());
	if (nullptr != RenderWindow)
	{
		WindowHandle = RenderWindow->GetRenderWindowHandle();
	}
	assert(WindowHandle != nullptr);

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	SwapChainDesc.BufferDesc.Width = RenderTarget->GetWidth();
	SwapChainDesc.BufferDesc.Height = RenderTarget->GetHeight();
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.SampleDesc.Count = 4;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.BufferCount = 2;
	SwapChainDesc.OutputWindow = WindowHandle;
	SwapChainDesc.Windowed = true;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	IDXGIFactory->CreateSwapChain(
		IDX12CommandQueue,
		&SwapChainDesc,
		&IDXGISwapChain);

	// Create render view description
	D3D12_DESCRIPTOR_HEAP_DESC RTDescriptorHeapDesc = {};
	RTDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	RTDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	RTDescriptorHeapDesc.NumDescriptors = 2;
	IDX12Device->CreateDescriptorHeap(&RTDescriptorHeapDesc, IID_PPV_ARGS(&IDX12DescriptorHeapRenderTarget));

	D3D12_DESCRIPTOR_HEAP_DESC DSDescriptorHeapDesc;
	DSDescriptorHeapDesc.NumDescriptors = 1;
	DSDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	DSDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	DSDescriptorHeapDesc.NodeMask = 0;
	IDX12Device->CreateDescriptorHeap(&DSDescriptorHeapDesc, IID_PPV_ARGS(&IDX12DescriptorHeapDepthStencil));

	RTVDescriptorSize = IDX12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	DSVDescriptorSize = IDX12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

	// Create render view
	int RTVDescriptorSize = IDX12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHandle(IDX12DescriptorHeapRenderTarget->GetCPUDescriptorHandleForHeapStart());
	IDX12Device->CreateRenderTargetView(IRenderTargets[0], nullptr, DescriptorHandle);
	IDX12Device->CreateRenderTargetView(IRenderTargets[1], nullptr, DescriptorHandle);
	FrameIndex = 0;

	// viewport
	ViewPort = { 0.0f, 0.0f, static_cast<float>(RenderTarget->GetWidth()), static_cast<float>(RenderTarget->GetHeight()), 0.0f, 1.0f };

	// Scissor Rectangle
	ScissorRect = { 0, 0, RenderTarget->GetWidth(), RenderTarget->GetHeight() };

	// Create root signature
	CD3DX12_ROOT_PARAMETER SlotRootParameter[1];

	CD3DX12_DESCRIPTOR_RANGE CVBTable;
	CVBTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
	SlotRootParameter[0].InitAsDescriptorTable(1, &CVBTable);

	CD3DX12_ROOT_SIGNATURE_DESC RootSignatureDesc(1, SlotRootParameter, 0, nullptr,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ID3DBlob* Signature;
	ID3DBlob* Error;
	D3D12SerializeRootSignature(&RootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &Signature, &Error);
	IDX12Device->CreateRootSignature(0, Signature->GetBufferPointer(), Signature->GetBufferSize(), IID_PPV_ARGS(&IDX12RootSignature));

	UINT CompileFlags = 0;
	std::wstring ShaderFileName(L"Shader\\Basic.hlsl");
	D3DCompileFromFile(ShaderFileName.c_str(), nullptr, nullptr, "VSMain", "vs_5_0", CompileFlags, 0, &VertexShader, nullptr);
	D3DCompileFromFile(ShaderFileName.c_str(), nullptr, nullptr, "PSMain", "ps_5_0", CompileFlags, 0, &PixelShader, nullptr);

	// Input Layout
	D3D12_INPUT_ELEMENT_DESC InputLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 } };

	UINT NumElements = sizeof(InputLayout) / sizeof(InputLayout[0]);

	VERTEX TriangleVertexes[] = {
	{ 0.0f, 0.5f, 0.0f,{ 1.0f, 0.0f, 0.0f, 1.0f } },
	{ 0.5f, -0.5, 0.0f,{ 0.0f, 1.0f, 0.0f, 1.0f } },
	{ -0.5f, -0.5f, 0.0f,{ 0.0f, 0.0f, 1.0f, 1.0f } } };

	// Create vertex buffer
	HRESULT Result = IDX12Device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 
		D3D12_HEAP_FLAG_NONE, 
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(TriangleVertexes)), 
		D3D12_RESOURCE_STATE_GENERIC_READ, 
		nullptr, 
		IID_PPV_ARGS(&VertexBuffer));

	// Copy data
	UINT8* VertexBufferData;
	VertexBuffer->Map(0, nullptr, reinterpret_cast<void**>(&VertexBufferData));
	memcpy(VertexBufferData, TriangleVertexes, sizeof(TriangleVertexes));
	VertexBuffer->Unmap(0, nullptr);

	// Vertex buffer view
	VertexBufferView.BufferLocation = VertexBuffer->GetGPUVirtualAddress();
	VertexBufferView.StrideInBytes = sizeof(VERTEX);
	VertexBufferView.SizeInBytes = sizeof(TriangleVertexes);

	// Create graphic pipeline state 
	D3D12_GRAPHICS_PIPELINE_STATE_DESC PSODesc = {};
	PSODesc.InputLayout = { InputLayout, NumElements };
	PSODesc.pRootSignature = IDX12RootSignature;
	PSODesc.DepthStencilState.DepthEnable = FALSE;
	PSODesc.DepthStencilState.StencilEnable = FALSE;
	//PSODesc.VS = CD3DX12_SHADER_BYTECODE(VertexShader);
	//PSODesc.PS = CD3DX12_SHADER_BYTECODE(PixelShader);
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
	FenceValue = 1;

	// Create event
	EventHandle = CreateEventEx(nullptr, FALSE, FALSE, EVENT_ALL_ACCESS);

	return 0;
}

int DX12Device::Draw()
{
	// Set root signature
	IDX12CommandList->SetGraphicsRootSignature(IDX12RootSignature);

	// Set view port
	IDX12CommandList->RSSetViewports(1, &ViewPort);

	// Set scissor
	IDX12CommandList->RSSetScissorRects(1, &ScissorRect);

	// Reset command list
	IDX12CommandList->Reset(IDX12CommandAllocator, IDX12PipleLineState);

	FrameIndex = 0;
	IDX12CommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(IRenderTargets[FrameIndex], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

	// Clear color and depth stencil
	float ClearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
	IDX12CommandList->ClearRenderTargetView(GetBackBufferView(), ClearColor, 0, nullptr);
	IDX12CommandList->ClearDepthStencilView(GetDepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	// Set render target
	IDX12CommandList->OMSetRenderTargets(1, &GetBackBufferView(), true, &GetDepthStencilView());

	// Draw
	IDX12CommandList->DrawIndexedInstanced(0, 1, 0, 0, 0);

	IDX12CommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(IRenderTargets[FrameIndex], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	IDX12CommandList->Close();

	// Execute command list
	ID3D12CommandList* CommandLists[] = { IDX12CommandList };
	IDX12CommandQueue->ExecuteCommandLists(1, CommandLists);

	// Present
	IDXGISwapChain->Present(0, 0);

	const UINT64 CmdFence = FenceValue;
	IDX12CommandQueue->Signal(IDX12Fence, CmdFence);
	FenceValue++;

	if (IDX12Fence->GetCompletedValue() < CmdFence)
	{
		IDX12Fence->SetEventOnCompletion(CmdFence, EventHandle);
		WaitForSingleObject(EventHandle, INFINITE);
	}

	return 0;
}

ID3D12Resource* DX12Device::GetBackBuffer() const
{
	return IRenderTargets[FrameIndex];
}

D3D12_CPU_DESCRIPTOR_HANDLE DX12Device::GetBackBufferView() const
{
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(
		IDX12DescriptorHeapDepthStencil->GetCPUDescriptorHandleForHeapStart(),
		FrameIndex,
		RTVDescriptorSize);

}

D3D12_CPU_DESCRIPTOR_HANDLE DX12Device::GetDepthStencilView() const
{
	return IDX12DescriptorHeapRenderTarget->GetCPUDescriptorHandleForHeapStart();
}
