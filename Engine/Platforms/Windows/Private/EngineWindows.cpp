#include "..\Public\EngineWindows.h"
#include "..\..\..\Frame\Public\Renderer.h"
#include "..\..\..\Frame\Public\Globals.h"
#include "..\Public\RenderWindowWindows.h"
#include "..\..\..\RenderDevices\Public\DX12Device.h"

template<> EngineWindows* EngineWindows::Singleton<EngineWindows>::Instance = nullptr;

int EngineWindows::Init()
{
	Device = new DX12Device();
	Renderer = new RealRenderer();
	RenderTarget = new RenderWindowWindows();
	RenderTarget->Init();

	return 0;
}

int EngineWindows::Tick()
{
	MSG Message = {};
	
	if (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);

		if (Message.message == WM_QUIT)
		{
			GExit = true;
		}
	}
	else
	{
		__super::Tick();
	}

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
