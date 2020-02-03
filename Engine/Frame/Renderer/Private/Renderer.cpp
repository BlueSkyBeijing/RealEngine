#include "..\Public\Renderer.h"
#include "..\..\Public\Engine.h"
#include <assert.h>


int RenderCommandList::Flush()
{
	return 0;
}

int RenderCommandList::reset()
{
	return 0;
}

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

int Renderer::Render()
{
	clear();

	computeVisibility();

	IDevice* Device = Engine::GetDevice();
	if (Device != nullptr)
	{
		Device->Draw();
	}

	return 0;
}

int Renderer::clear()
{
	return 0;
}

void Renderer::computeVisibility()
{

}
