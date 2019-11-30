#include "..\Public\Engine.h"
#include "..\Public\Renderer.h"
#include "..\Public\Globals.h"


template<> RealEngine* RealEngine::Singleton<RealEngine>::Instance = nullptr;

int RealEngine::Init()
{
	Renderer = new RealRenderer();
	Device = new DX12Device();
	RenderTarget = new RenderTargetWindow();
	RenderTarget->Initialize();

	return 0;
}

int RealEngine::Tick()
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

int RealEngine::Exit()
{
	delete Renderer;

	return 0;
}

IDevice* RealEngine::GetDevice()
{
	return Device;
}

HINSTANCE RealEngine::GetInstanceHandle()
{
	return InstanceHandle;
}

void RealEngine::SetInstanceHandle(HINSTANCE Instance)
{
	InstanceHandle = Instance;
}
