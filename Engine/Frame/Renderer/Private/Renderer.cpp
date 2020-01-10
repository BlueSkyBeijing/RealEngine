#include "..\Public\Renderer.h"
#include "..\..\Public\Engine.h"
#include <assert.h>

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

int Renderer::Render()
{
	computeVisibility();

	IDevice* Device = Engine::GetDevice();
	if (Device != nullptr)
	{
		Device->Draw();
	}

	return 0;
}

void Renderer::computeVisibility()
{

}
