#pragma once
#include "..\Renderer\Public\Renderer.h"
#include "..\Public\Device.h"
#include "..\..\Utility\Public\Singleton.h"
#include "..\Public\RenderTarget.h"
#include "..\Public\Scene.h"
#include "..\Public\SceneManager.h"
#include <windows.h>
#include <string>

class IEngine
{
public:
	virtual int Init() = 0;

	virtual int Tick() = 0;

	virtual int Loop() = 0;

	virtual int Exit() = 0;

	virtual int Launch() = 0;

};


class Engine : public IEngine
{
public:

	virtual int Init() override;

	virtual int Tick() override;

	virtual int Loop() override;

	virtual int Exit() override;

	virtual int Launch() override;

	static IDevice* GetDevice();

	IScene* GetCurrentScene();

	IRenderTarget* GetRenderTarget();

	bool LoadScene(std::string FileName);

protected:
	static IDevice* Device;
	IRenderer* mRenderer;
	IRenderTarget* mRenderTargetMain;
	IScene* mCurrentScene;
	ISceneManager* mSceneManager;
};

