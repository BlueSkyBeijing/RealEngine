#include "..\Public\Engine.h"
#include "..\Renderer\Public\Renderer.h"
#include "..\Public\Globals.h"
#include "..\..\Platforms\Windows\Public\RenderWindowWindows.h"

IDevice* Engine::Device = nullptr;

int Engine::Init()
{
	return 0;
}

int Engine::Tick()
{
	if (mRenderer != nullptr)
	{
		mRenderer->Render();
	}

	return 0;
}

int Engine::Exit()
{
	if (mRenderer != nullptr)
	{
		delete mRenderer;
	}

	if (mRenderTargetMain != nullptr)
	{
		delete mRenderTargetMain;
	}

	if (Device != nullptr)
	{
		delete Device;
	}

	return 0;
}

IDevice* Engine::GetDevice()
{
	return Device;
}

IRenderTarget* Engine::GetRenderTarget()
{
	return mRenderTargetMain;
}
