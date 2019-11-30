#include "Engine\Public\Engine.h"
#include "Engine\Public\Globals.h"
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	RealEngine::GetInstance()->SetInstanceHandle(hInstance);

	RealEngine::GetInstance()->Init();

	while (!GExit)
	{
		RealEngine::GetInstance()->Tick();
	}

	RealEngine::GetInstance()->Exit();

	return 0;
}
