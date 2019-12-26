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
	IDevice* Device = Engine::GetDevice();
	assert(Device != nullptr);
	Device->Draw();

	return 0;
}

void Renderer::ComputeVisibility()
{

}
