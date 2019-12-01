#pragma once
#include "..\Public\Renderer.h"
#include "..\Public\Device.h"
#include "..\..\Utility\Public\Singleton.h"
#include "..\Public\RenderTarget.h"
#include <windows.h>

class IEngine
{
public:
	virtual int Init() = 0;

	virtual int Tick() = 0;

	virtual int Exit() = 0;
};


class RealEngine : public IEngine
{
public:

	virtual int Init() override;

	virtual int Tick() override;

	virtual int Exit() override;

	static IDevice* GetDevice();

protected:
	static IDevice* Device;
	IRenderer* Renderer;
	IRenderTarget* RenderTarget;
};

