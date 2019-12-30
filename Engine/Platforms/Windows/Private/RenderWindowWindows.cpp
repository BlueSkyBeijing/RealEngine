#include "..\..\..\Frame\Public\RenderTarget.h"
#include "..\..\..\Frame\Public\Engine.h"
#include "..\Public\RenderWindowWindows.h"
#include "..\Public\EngineWindows.h"
#include "..\..\..\Frame\Public\Globals.h"


RenderWindowWindows::RenderWindowWindows()
{

}

RenderWindowWindows::~RenderWindowWindows()
{

}

int RenderWindowWindows::Init()
{
	__super::Init();

	RenderWindowHandle = GetActiveWindow();

	return 0;
}

HWND RenderWindowWindows::GetRenderWindowHandle()
{
	return RenderWindowHandle;
}
