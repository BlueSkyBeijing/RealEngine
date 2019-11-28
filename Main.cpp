#include "Engine\Public\Engine.h"
#include "Engine\Public\Globals.h"

int main()
{
	RealEngine::GetInstance()->Init();

	while (!GExit)
	{
		RealEngine::GetInstance()->Tick();
	}

	RealEngine::GetInstance()->Exit();

	return 0;
}
