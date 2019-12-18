#include "..\Public\DX12Device.h"
#include "..\..\..\Frame\Public\RenderTarget.h"
#include "..\..\..\Platforms\Windows\Public\EngineWindows.h"
#include "..\..\..\Platforms\Windows\Public\RenderWindowWindows.h"

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")


struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

DX12Device::DX12Device()
{

}

DX12Device::~DX12Device()
{

}

int DX12Device::Init()
{
#if defined(DEBUG) || defined(_DEBUG) 
	// Enable DX12 debug layer
	{
		ID3D12Debug* DebugController;
		D3D12GetDebugInterface(IID_PPV_ARGS(&DebugController));
		DebugController->EnableDebugLayer();
	}
#endif

	SwapChainBufferCount = 2;
	ChainBufferndex = 0;
	BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	CreateDevice();
	CreateCommandObjects();
	CreateSwapChain();

	// Create swipe chain
	IRenderTarget* RenderTarget = EngineWindows::GetInstance()->GetRenderTarget();
	assert(RenderTarget != nullptr);

	// Create render view description
	D3D12_DESCRIPTOR_HEAP_DESC RTDescriptorHeapDesc;
	RTDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	RTDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	RTDescriptorHeapDesc.NumDescriptors = SwapChainBufferCount;
	RTDescriptorHeapDesc.NodeMask = 0;
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
	CD3DX12_CPU_DESCRIPTOR_HANDLE DescriptorHandle(IDX12DescriptorHeapRenderTarget->GetCPUDescriptorHandleForHeapStart());
	for (UINT i = 0; i < SwapChainBufferCount; i++)
	{
		IDXGISwapChain->GetBuffer(i, IID_PPV_ARGS(&IRenderTargets[i]));
		IDX12Device->CreateRenderTargetView(IRenderTargets[i], nullptr, DescriptorHandle);
		DescriptorHandle.Offset(1, RTVDescriptorSize);
	}
	ChainBufferndex = 0;

	// Create the depth/stencil buffer and view.
	D3D12_RESOURCE_DESC DepthStencilDesc;
	DepthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	DepthStencilDesc.Alignment = 0;
	DepthStencilDesc.Width = RenderTarget->GetWidth();
	DepthStencilDesc.Height = RenderTarget->GetHeight();
	DepthStencilDesc.DepthOrArraySize = 1;
	DepthStencilDesc.MipLevels = 1;
	DepthStencilDesc.Format = DepthStencilFormat;
	DepthStencilDesc.SampleDesc.Count = 1;
	DepthStencilDesc.SampleDesc.Quality = 0;
	DepthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	DepthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE ClearValue;
	ClearValue.Format = DepthStencilFormat;
	ClearValue.DepthStencil.Depth = 1.0f;
	ClearValue.DepthStencil.Stencil = 0;
	HRESULT Result = IDX12Device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&DepthStencilDesc,
		D3D12_RESOURCE_STATE_COMMON,
		&ClearValue,
		IID_PPV_ARGS(&DepthStencilBuffer));

	// viewport
	ViewPort = { 0.0f, 0.0f, static_cast<float>(RenderTarget->GetWidth()), static_cast<float>(RenderTarget->GetHeight()), 0.0f, 1.0f };

	// Scissor Rectangle
	ScissorRect = { 0, 0, RenderTarget->GetWidth(), RenderTarget->GetHeight() };

	UINT CompileFlags = 0;
	std::wstring ShaderFileName(L"Engine\\Shaders\\Basic.hlsl");

	Result = D3DCompileFromFile(ShaderFileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VSMain", "vs_5_0", CompileFlags, 0, &VertexShader, nullptr);
	Result = D3DCompileFromFile(ShaderFileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PSMain", "ps_5_0", CompileFlags, 0, &PixelShader, nullptr);

	// Input Layout
	D3D12_INPUT_ELEMENT_DESC InputLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 } };

	UINT NumElements = sizeof(InputLayout) / sizeof(InputLayout[0]);

	std::array<Vertex, 8> Vertexes =
	{
		Vertex({ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::White) }),
		Vertex({ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Black) }),
		Vertex({ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Red) }),
		Vertex({ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Green) }),
		Vertex({ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4(Colors::Blue) }),
		Vertex({ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT4(Colors::Yellow) }),
		Vertex({ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT4(Colors::Cyan) }),
		Vertex({ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT4(Colors::Magenta) })
	};

	std::array<std::uint16_t, 36> Indexes =
	{
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	IndexCount = (UINT)Indexes.size();

	float x = 6.0f * sinf(0.0);
	float z = 6.0f * sinf(0.0);
	float y = 6.0f * cosf(0.0);

	// Build view matrix.
	XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
	XMStoreFloat4x4(&ViewMatrix, view);

	const float PI = 3.1415926f;
	float AspectRatio = (float) RenderTarget->GetWidth() / (float) RenderTarget->GetHeight();
	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * PI, AspectRatio, 1.0f, 1000.0f);
	XMStoreFloat4x4(&ProjMatrix, P);

	WorldMatrix = DirectX::XMFLOAT4X4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	XMMATRIX world = XMLoadFloat4x4(&WorldMatrix);
	XMMATRIX proj = XMLoadFloat4x4(&ProjMatrix);
	XMMATRIX worldViewProj = world * view * proj;

	XMFLOAT4X4 WorldViewProj;
	XMStoreFloat4x4(&WorldViewProj, XMMatrixTranspose(worldViewProj));

	// Create vertex buffer
	Result = IDX12Device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 
		D3D12_HEAP_FLAG_NONE, 
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(Vertexes)),
		D3D12_RESOURCE_STATE_GENERIC_READ, 
		nullptr, 
		IID_PPV_ARGS(&VertexBuffer));

	// Create index buffer
	Result = IDX12Device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(Indexes)),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&IndexBuffer));

	// Create constant buffer
	Result = IDX12Device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(CalcConstantBufferByteSize(sizeof(XMMATRIX))),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&ConstantBuffer));

	const UINT VBByteSize = (UINT)Vertexes.size() * sizeof(Vertex);
	const UINT IBByteSize = (UINT)Indexes.size() * sizeof(std::uint16_t);

	// Copy data
	UINT8* VertexBufferData;
	VertexBuffer->Map(0, nullptr, reinterpret_cast<void**>(&VertexBufferData));
	memcpy(VertexBufferData, Vertexes.data(), VBByteSize);
	VertexBuffer->Unmap(0, nullptr);

	UINT8* IndexBufferData;
	IndexBuffer->Map(0, nullptr, reinterpret_cast<void**>(&IndexBufferData));
	memcpy(IndexBufferData, Indexes.data(), IBByteSize);
	IndexBuffer->Unmap(0, nullptr);

	UINT8* ConstantBufferData;
	ConstantBuffer->Map(0, nullptr, reinterpret_cast<void**>(&ConstantBufferData));
	memcpy(ConstantBufferData, &WorldViewProj, sizeof(WorldViewProj));
	ConstantBuffer->Unmap(0, nullptr);

	// Vertex buffer view
	VertexBufferView.BufferLocation = VertexBuffer->GetGPUVirtualAddress();
	VertexBufferView.StrideInBytes = sizeof(Vertex);
	VertexBufferView.SizeInBytes = VBByteSize;

	IndexBufferView.BufferLocation = IndexBuffer->GetGPUVirtualAddress();
	IndexBufferView.Format = DXGI_FORMAT_R16_UINT;
	IndexBufferView.SizeInBytes = IBByteSize;;


	D3D12_DESCRIPTOR_HEAP_DESC CBVHeapDesc;
	CBVHeapDesc.NumDescriptors = 1;
	CBVHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	CBVHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	CBVHeapDesc.NodeMask = 0;
	Result = IDX12Device->CreateDescriptorHeap(&CBVHeapDesc,
		IID_PPV_ARGS(&ConstantBufferHeap));

	D3D12_CONSTANT_BUFFER_VIEW_DESC CBVDesc;
	CBVDesc.BufferLocation = ConstantBuffer->GetGPUVirtualAddress();
	CBVDesc.SizeInBytes = CalcConstantBufferByteSize(sizeof(XMMATRIX));

	IDX12Device->CreateConstantBufferView(
		&CBVDesc,
		ConstantBufferHeap->GetCPUDescriptorHandleForHeapStart());

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

	// Create graphic pipeline state 
	D3D12_GRAPHICS_PIPELINE_STATE_DESC PSODesc;
	ZeroMemory(&PSODesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	PSODesc.InputLayout = { InputLayout, NumElements };
	PSODesc.pRootSignature = IDX12RootSignature;
	PSODesc.DepthStencilState.DepthEnable = TRUE;
	PSODesc.DepthStencilState.StencilEnable = TRUE;
	PSODesc.VS =
	{
		reinterpret_cast<BYTE*>(VertexShader->GetBufferPointer()),
		VertexShader->GetBufferSize()
	};
	PSODesc.PS =
	{
		reinterpret_cast<BYTE*>(PixelShader->GetBufferPointer()),
		PixelShader->GetBufferSize()
	};
	PSODesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	PSODesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	PSODesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	PSODesc.SampleMask = UINT_MAX;
	PSODesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	PSODesc.NumRenderTargets = 1;
	PSODesc.RTVFormats[0] = BackBufferFormat;
	PSODesc.SampleDesc.Count = 1;
	PSODesc.SampleDesc.Quality = 0;
	PSODesc.DSVFormat = DepthStencilFormat;
	IDX12Device->CreateGraphicsPipelineState(&PSODesc, IID_PPV_ARGS(&IDX12PipleLineState));

	// Crete fence
	IDX12Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&IDX12Fence));
	FenceValue = 1;

	// Create event
	EventHandle = CreateEventEx(nullptr, FALSE, FALSE, EVENT_ALL_ACCESS);

	FlushCommandQueue();

	// Create descriptor to mip level 0 of entire resource using the format of the resource.
	D3D12_DEPTH_STENCIL_VIEW_DESC DSVDesc;
	DSVDesc.Flags = D3D12_DSV_FLAG_NONE;
	DSVDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	DSVDesc.Format = DepthStencilFormat;
	DSVDesc.Texture2D.MipSlice = 0;
	IDX12Device->CreateDepthStencilView(DepthStencilBuffer, &DSVDesc, GetDepthStencilView());

	IDX12CommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(DepthStencilBuffer,
		D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));

	IDX12CommandList->Close();

	// Execute command list
	ID3D12CommandList* CommandLists[] = { IDX12CommandList };
	IDX12CommandQueue->ExecuteCommandLists(1, CommandLists);

	FlushCommandQueue();

	return 0;
}

int DX12Device::Draw()
{
	IDX12CommandAllocator->Reset();

	// Reset command list
	IDX12CommandList->Reset(IDX12CommandAllocator, IDX12PipleLineState);

	// Set view port
	IDX12CommandList->RSSetViewports(1, &ViewPort);

	// Set scissor
	IDX12CommandList->RSSetScissorRects(1, &ScissorRect);

	IDX12CommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(GetBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

	// Clear color and depth stencil
	float ClearColor[] = { 0.690196097f, 0.768627524f, 0.870588303f, 1.000000000f };
	IDX12CommandList->ClearRenderTargetView(GetBackBufferView(), ClearColor, 0, nullptr);
	IDX12CommandList->ClearDepthStencilView(GetDepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	// Set render target
	IDX12CommandList->OMSetRenderTargets(1, &GetBackBufferView(), true, &GetDepthStencilView());
	IDX12CommandList->SetDescriptorHeaps(1, &ConstantBufferHeap);

	// Set root signature
	IDX12CommandList->SetGraphicsRootSignature(IDX12RootSignature);

	IDX12CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	IDX12CommandList->IASetVertexBuffers(0, 1, &VertexBufferView);
	IDX12CommandList->IASetIndexBuffer(&IndexBufferView);
	IDX12CommandList->SetGraphicsRootDescriptorTable(0, ConstantBufferHeap->GetGPUDescriptorHandleForHeapStart());

	// Draw
	IDX12CommandList->DrawIndexedInstanced(IndexCount, 1, 0, 0, 0);

	IDX12CommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(GetBackBuffer(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	IDX12CommandList->Close();

	// Execute command list
	ID3D12CommandList* CommandLists[] = { IDX12CommandList };
	IDX12CommandQueue->ExecuteCommandLists(1, CommandLists);

	// Present
	IDXGISwapChain->Present(0, 0);

	ChainBufferndex = (ChainBufferndex + 1) % SwapChainBufferCount;

	FlushCommandQueue();

	return 0;
}

void DX12Device::CreateDevice()
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
}

void DX12Device::CreateCommandObjects()
{
	// Create command queue
	D3D12_COMMAND_QUEUE_DESC QueueDesc = {};
	QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	IDX12Device->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&IDX12CommandQueue));

	// Create command allocator
	IDX12Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&IDX12CommandAllocator));

	// Create command list
	IDX12Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, IDX12CommandAllocator, IDX12PipleLineState, IID_PPV_ARGS(&IDX12CommandList));

	IDX12CommandList->Close();
}

void DX12Device::CreateSwapChain()
{
	HWND WindowHandle = nullptr;
	RenderWindowWindows *RenderWindow = dynamic_cast<RenderWindowWindows*>(EngineWindows::GetInstance()->GetRenderTarget());
	if (nullptr != RenderWindow)
	{
		WindowHandle = RenderWindow->GetRenderWindowHandle();
	}
	assert(WindowHandle != nullptr);

	IRenderTarget* RenderTarget = EngineWindows::GetInstance()->GetRenderTarget();
	assert(RenderTarget != nullptr);

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	SwapChainDesc.BufferDesc.Width = RenderTarget->GetWidth();
	SwapChainDesc.BufferDesc.Height = RenderTarget->GetHeight();
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.Format = BackBufferFormat;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.BufferCount = 2;
	SwapChainDesc.OutputWindow = WindowHandle;
	SwapChainDesc.Windowed = true;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT Result = IDXGIFactory->CreateSwapChain(
		IDX12CommandQueue,
		&SwapChainDesc,
		&IDXGISwapChain);

}

void DX12Device::CreateGeometry()
{

}

ID3D12Resource* DX12Device::GetBackBuffer() const
{
	return IRenderTargets[ChainBufferndex];
}

D3D12_CPU_DESCRIPTOR_HANDLE DX12Device::GetBackBufferView() const
{
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(
		IDX12DescriptorHeapRenderTarget->GetCPUDescriptorHandleForHeapStart(),
		ChainBufferndex,
		RTVDescriptorSize);

}

D3D12_CPU_DESCRIPTOR_HANDLE DX12Device::GetDepthStencilView() const
{
	return IDX12DescriptorHeapDepthStencil->GetCPUDescriptorHandleForHeapStart();
}

void DX12Device::FlushCommandQueue()
{
	const UINT64 CmdFence = FenceValue;
	IDX12CommandQueue->Signal(IDX12Fence, CmdFence);
	FenceValue++;

	if (IDX12Fence->GetCompletedValue() < CmdFence)
	{
		IDX12Fence->SetEventOnCompletion(CmdFence, EventHandle);
		WaitForSingleObject(EventHandle, INFINITE);
	}
}
