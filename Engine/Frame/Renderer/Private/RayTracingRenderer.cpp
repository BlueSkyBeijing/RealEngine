#include "..\Public\RayTracingRenderer.h"
#include "..\..\Public\Engine.h"
#include <assert.h>

RayTracingRenderer::RayTracingRenderer()
{

}

RayTracingRenderer::~RayTracingRenderer()
{

}

int RayTracingRenderer::Render()
{
	IDevice* Device = Engine::GetDevice();
	assert(Device != nullptr);
	Device->Draw();

	return 0;
}

bool RayTracingRenderer::RenderOpaquePass()
{
	return true;
}

bool RayTracingRenderer::RenderTranslucency()
{
	return true;
}
