#include "..\Public\EngineWindows.h"
#include "..\..\..\Frame\Renderer\Public\Renderer.h"
#include "..\..\..\Frame\Public\Globals.h"
#include "..\Public\RenderWindowWindows.h"
#include "..\..\..\RenderDevices\DX12\Public\DX12Device.h"
#if RENDER_DEVICE_USE == RENDER_DEVICE_DX12
#include "..\..\..\RenderDevices\DX12\Public\DX12Device.h"
#elif RENDER_DEVICE_USE == RENDER_DEVICE_VULKAN1
#include "..\..\..\RenderDevices\Vulkan1\Public\Vulkan1Device.h"
#elif RENDER_DEVICE_USE == RENDER_DEVICE_GL4
#include "..\..\..\RenderDevices\GL4\Public\GL4Device.h"
#endif

template<> EngineWindows* EngineWindows::Singleton<EngineWindows>::Instance = nullptr;

int EngineWindows::Init()
{
	mRenderTargetMain = new RenderWindowWindows();
	mRenderTargetMain->Init();

#if RENDER_DEVICE_USE == RENDER_DEVICE_DX12
	Device = new DX12Device();
	Device->Init();
	mRenderer = new Renderer();
#elif RENDER_DEVICE_USE == RENDER_DEVICE_VULKAN1
	Device = new Vulkan1Device();
	Device->Init();
	mRenderer = new Renderer();
#elif RENDER_DEVICE_USE == RENDER_DEVICE_GL4
	Device = new GL4Device();
	Device->Init();
	mRenderer = new Renderer();
#endif

	return 0;
}

int EngineWindows::Tick()
{
	__super::Tick();

	return 0;
}

int EngineWindows::Exit()
{
	__super::Exit();

	return 0;
}
