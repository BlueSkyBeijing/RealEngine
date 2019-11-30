#pragma once
#include "..\Public\Renderer.h"
#include "..\Public\Device.h"
#include "..\Public\Singleton.h"
#include "..\Public\RenderTarget.h"
#include <windows.h>

class IEngine
{
public:
	virtual int Init() = 0;

	virtual int Tick() = 0;

	virtual int Exit() = 0;

	virtual IDevice* GetDevice() = 0;

};


class RealEngine : public IEngine, public Singleton<RealEngine>
{
public:

	virtual int Init() override;

	virtual int Tick() override;

	virtual int Exit() override;

	virtual IDevice* GetDevice() override;


	HINSTANCE GetInstanceHandle();
	void SetInstanceHandle(HINSTANCE Instance);

private:
	IRenderer* Renderer;
	IDevice* Device;
	IRenderTarget* RenderTarget;

	HINSTANCE InstanceHandle;
};

