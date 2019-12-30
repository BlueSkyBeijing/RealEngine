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
#if WINDOWS_RENDER_DEVICE == USE_DX12
	//MSG Message = {};

	//if (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
	//{
	//	TranslateMessage(&Message);
	//	DispatchMessage(&Message);

	//	if (Message.message == WM_QUIT)
	//	{
	//		GExit = true;
	//	}
	//}
	//else
	//{
	//	__super::Tick();
	//}

	static_cast<RenderWindowWindows*>(mRenderTargetMain)->Update();
	if (!GExit)
	{
		__super::Tick();
	}

#else
	static_cast<RenderWindowWindows*>(mRenderTargetMain)->Update();
#endif

	return 0;
}

int EngineWindows::Exit()
{
	__super::Exit();

	return 0;
}

HINSTANCE EngineWindows::GetInstanceHandle()
{
	return InstanceHandle;
}

void EngineWindows::SetInstanceHandle(HINSTANCE Instance)
{
	InstanceHandle = Instance;
}

LRESULT EngineWindows::MessageProcess(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYUP:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
