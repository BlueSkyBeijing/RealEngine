#pragma once
#include "..\Public\Renderer.h"
#include "..\Public\Device.h"
#include "..\Public\Singleton.h"

class IEngine
{
public:
	virtual int Init() = 0;

	virtual int Tick() = 0;

	virtual int Exit() = 0;
};


class RealEngine : public IEngine, public Singleton<RealEngine>
{
public:

	virtual int Init() override;

	virtual int Tick() override;

	virtual int Exit() override;

	IDevice* GetDevice();

private:
	IRenderer* Renderer;
	IDevice* Device;
};

