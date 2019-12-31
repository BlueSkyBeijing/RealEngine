#include "..\..\..\Frame\Public\Engine.h"
#include "..\..\..\Frame\Public\Globals.h"
#include "..\Public\EngineWindows.h"

#include <windows.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	EngineWindows::GetInstance()->Launch();

	return 0;
}
