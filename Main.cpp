#include "Engine\Public\Engine.h"
#include "Engine\Public\Globals.h"

RealEngine GEngine;

int main()
{
	GEngine.Init();

	while (!GExit)
	{
		GEngine.Tick();
	}

	GEngine.Exit();

	return 0;
}
