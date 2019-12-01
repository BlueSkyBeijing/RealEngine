#include "..\Public\Engine.h"
#include "..\Public\Renderer.h"
#include "..\Public\Globals.h"
#include "..\..\Platforms\Windows\Public\RenderWindow.h"

IDevice* RealEngine::Device = nullptr;

int RealEngine::Init()
{
	return 0;
}

int RealEngine::Tick()
{
	if (Renderer != nullptr)
	{
		Renderer->Render();
	}

	return 0;
}

int RealEngine::Exit()
{
	if (Renderer != nullptr)
	{
		delete Renderer;
	}

	return 0;
}

IDevice* RealEngine::GetDevice()
{
	return Device;
}
