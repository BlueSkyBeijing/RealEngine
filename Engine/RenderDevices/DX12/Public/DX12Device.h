#pragma once
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
	void CreateDevice();
	void CreateCommandObjects();
	void CreateSwapChain();
	void CreateGeometry();
	void LoadTexture();

	ID3D12Resource* GetBackBuffer() const;
	D3D12_CPU_DESCRIPTOR_HANDLE GetBackBufferView() const;
	D3D12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView() const;
	void FlushCommandQueue();

private:
	Microsoft::WRL::ComPtr <IDXGIFactory2>  mDXGIFactory;
	Microsoft::WRL::ComPtr <IDXGIAdapter1> mAdapter;
	Microsoft::WRL::ComPtr <ID3D12Device> mDX12Device;
	Microsoft::WRL::ComPtr <ID3D12CommandQueue> mDX12CommandQueue;
	Microsoft::WRL::ComPtr <ID3D12CommandAllocator> mDX12CommandAllocator;
	Microsoft::WRL::ComPtr <ID3D12GraphicsCommandList> mDX12CommandList;
	Microsoft::WRL::ComPtr <IDXGISwapChain> mDXGISwapChain;
	Microsoft::WRL::ComPtr <ID3D12RootSignature> mDX12RootSignature;
	Microsoft::WRL::ComPtr <ID3D12PipelineState> mIDX12PipleLineState;
	Microsoft::WRL::ComPtr <ID3D12Fence> mDX12Fence;
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> mDX12DescriptorHeapRenderTarget;
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> mDX12DescriptorHeapDepthStencil;
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> mSRVDescriptorHeap;
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> mConstantBufferHeap;
	Microsoft::WRL::ComPtr <ID3D12Resource> mRenderTargets[2];
	Microsoft::WRL::ComPtr <ID3D12Resource> mDepthStencilBuffer;
	Microsoft::WRL::ComPtr <ID3D12Resource> mTestTexture;
	Microsoft::WRL::ComPtr <ID3D12Resource> mTestTextureUploadHeap;
	Microsoft::WRL::ComPtr <ID3DBlob> mVertexShader;
	Microsoft::WRL::ComPtr <ID3DBlob> mPixelShader;
	Microsoft::WRL::ComPtr <ID3D12Resource> mVertexBuffer;
	Microsoft::WRL::ComPtr <ID3D12Resource> mIndexBuffer;
	Microsoft::WRL::ComPtr <ID3D12Resource> mConstantBuffer;

	HANDLE mEventHandle;
	UINT64 mFenceValue;
	D3D12_VIEWPORT mViewPort;
	D3D12_RECT mScissorRect;
	D3D12_VERTEX_BUFFER_VIEW mVertexBufferView;
	D3D12_INDEX_BUFFER_VIEW mIndexBufferView;
	UINT mChainBufferndex;
	UINT mSwapChainBufferCount;
	UINT mRTVDescriptorSize;
	UINT mDSVDescriptorSize;
	UINT mCBVSRVDescriptorSize;
	XMFLOAT4X4 mWorldMatrix;
	XMFLOAT4X4 mViewMatrix;
	XMFLOAT4X4 mProjMatrix;
	UINT mIndexCount;
	DXGI_FORMAT mBackBufferFormat;
	DXGI_FORMAT mDepthStencilFormat;
};
