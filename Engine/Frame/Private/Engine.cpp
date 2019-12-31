#include "..\Public\Engine.h"
#include "..\Renderer\Public\Renderer.h"
#include "..\Public\Globals.h"
#include "..\..\Platforms\Windows\Public\RenderWindowWindows.h"
#include <SDL.h>

IDevice* Engine::Device = nullptr;

int Engine::Init()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	return 0;
}

int Engine::Tick()
{
	if (mRenderer != nullptr)
	{
		mRenderer->Render();
	}

	SDL_Event evt;
	if (SDL_PollEvent(&evt))
	{
		if (evt.type == SDL_QUIT)
		{
			GExit = true;
		}
	}

	return 0;
}

int Engine::Loop()
{
	while (!GExit)
	{
		Tick();
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

	SDL_Quit();

	return 0;
}

int Engine::Launch()
{
	Init();

	Loop();

	Exit();

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
