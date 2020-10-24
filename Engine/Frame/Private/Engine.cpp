#include "..\Public\Engine.h"
#include "..\Renderer\Public\Renderer.h"
#include "..\Public\Globals.h"
#include "..\..\Platforms\Windows\Public\RenderWindowWindows.h"
#include "..\Public\InputManager.h"

#include <SDL.h>

IDevice* Engine::Device = nullptr;

int Engine::Init()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	LoadScene("DefualtScene");

	mSceneManager = new SceneManager(mCurrentScene);
    mInputManager = new InputManager();

	return 0;
}

int Engine::Tick()
{
	if (mRenderer != nullptr)
	{
		mSceneManager->UpdateRenderList(mRenderer);
		mRenderer->Render();
	}

	SDL_Event evt;
	if (SDL_PollEvent(&evt))
	{
		if (evt.type == SDL_QUIT)
		{
			GExit = true;
		}
		else if (evt.type == SDL_KEYDOWN)
		{
            IScene* CurrentScene = mSceneManager->GetScene();
            ICamera* CurrentCamera = CurrentScene->GetCurrentCamera();

			int key = evt.key.keysym.sym;
			if (key == SDLK_w)
			{
				Eigen::Vector3f CameraPos = CurrentCamera->GetPosition();
                Eigen::Vector3f CameraDirection = CurrentCamera->GetDirection();
				CameraPos += CameraDirection * 0.1f;
                CurrentCamera->SetPosition(CameraPos);
			}
			else if (key == SDLK_s)
            {
                Eigen::Vector3f CameraPos = CurrentCamera->GetPosition();
                Eigen::Vector3f CameraDirection = CurrentCamera->GetDirection();
                CameraPos -= CameraDirection * 0.1f;
                CurrentCamera->SetPosition(CameraPos);
            }
			else if (key == SDLK_a)
            {
            }
            else if (key == SDLK_d)
            {
            }
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

IScene* Engine::GetCurrentScene()
{
	return mCurrentScene;
}

bool Engine::LoadScene(std::string FileName)
{
	mCurrentScene = new Scene();
	mCurrentScene->Load();
	return true;
}
