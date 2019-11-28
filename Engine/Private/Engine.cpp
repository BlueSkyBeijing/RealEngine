#include "..\Public\Engine.h"
#include "..\Public\Renderer.h"

template<> RealEngine* RealEngine::Singleton<RealEngine>::Instance = nullptr;

int RealEngine::Init()
{
	Renderer = new RealRenderer();
	Device = new DX12Device();

	return 0;
}

int RealEngine::Tick()
{
	Renderer->Render();

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
