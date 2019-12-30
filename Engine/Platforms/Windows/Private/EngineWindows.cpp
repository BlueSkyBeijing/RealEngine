#include "..\Public\EngineWindows.h"
#include "..\..\..\Frame\Renderer\Public\Renderer.h"
#include "..\..\..\Frame\Public\Globals.h"
#include "..\Public\RenderWindowWindows.h"
#include "..\..\..\RenderDevices\DX12\Public\DX12Device.h"

template<> EngineWindows* EngineWindows::Singleton<EngineWindows>::Instance = nullptr;

int EngineWindows::Init()
{
	mRenderTargetMain = new RenderWindowWindows();
	mRenderTargetMain->Init();

#if WINDOWS_RENDER_DEVICE == USE_DX12
	Device = new DX12Device();
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
