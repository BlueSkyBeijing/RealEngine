#include "..\Public\EngineWindows.h"
#include "..\..\..\Frame\Public\Renderer.h"
#include "..\..\..\Frame\Public\Globals.h"
#include "..\Public\RenderWindow.h"
#include "..\..\..\RenderDevices\Public\DX12Device.h"

template<> EngineWindows* EngineWindows::Singleton<EngineWindows>::Instance = nullptr;

int EngineWindows::Init()
{
	Device = new DX12Device();
	Renderer = new RealRenderer();
	RenderTarget = new RenderWindow();
	RenderTarget->Initialize();

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
		Renderer->Render();
	}

	return 0;
}

int EngineWindows::Exit()
{
	if (Renderer != nullptr)
	{
		delete Renderer;
	}

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
