#pragma once
#include "..\..\..\Frame\Renderer\Public\Renderer.h"
#include "..\..\..\Frame\Public\Device.h"
#include "..\..\..\Utility\Public\Singleton.h"
#include "..\..\..\Frame\Public\RenderTarget.h"
#include "..\..\..\Frame\Public\Engine.h"

#include <windows.h>

#define USE_DX12 1
#define USE_VULKAN 2
#define WINDOWS_RENDER_DEVICE USE_DX12

class EngineWindows : public Engine, public Singleton<EngineWindows>
{
public:

	virtual int Init() override;

	virtual int Tick() override;

	virtual int Exit() override;

private:
};

