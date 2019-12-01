#pragma once
#include "..\..\..\Frame\Public\Renderer.h"
#include "..\..\..\Frame\Public\Device.h"
#include "..\..\..\Utility\Public\Singleton.h"
#include "..\..\..\Frame\Public\RenderTarget.h"
#include "..\..\..\Frame\Public\Engine.h"

#include <windows.h>


class EngineWindows : public RealEngine, public Singleton<EngineWindows>
{
public:

	virtual int Init() override;

	virtual int Tick() override;

	virtual int Exit() override;

	HINSTANCE GetInstanceHandle();
	void SetInstanceHandle(HINSTANCE Instance);

private:
	HINSTANCE InstanceHandle;
};

