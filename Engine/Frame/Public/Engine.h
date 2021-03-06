#pragma once
#include "..\Renderer\Public\Renderer.h"
#include "Device.h"
#include "..\Utility\Public\Singleton.h"
#include "RenderTarget.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Camera.h"
#include "SceneObject.h"
#include "Texture.h"
#include <windows.h>
#include <string>

class ICamera;
class IDevice;
class IRenderer;
class IScene;
class ISceneManager;
class IInputManager;
class ISceneObject;
class IRenderTarget;
class ITexture;

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
    IInputManager* mInputManager;
};

