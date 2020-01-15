#include "..\Public\ForwardShadingRenderer.h"
#include "..\..\Public\Engine.h"
#include <assert.h>

ForwardShadingRenderer::ForwardShadingRenderer()
{

}

ForwardShadingRenderer::~ForwardShadingRenderer()
{

}

int ForwardShadingRenderer::Render()
{
	computeVisibility();

	renderShadowDepth();

	renderOpaque();

	renderTranslucency();

	return 0;
}

bool ForwardShadingRenderer::renderShadowDepth()
{
	IDevice* Device = Engine::GetDevice();
	assert(Device != nullptr);
	Device->Draw();

	return true;
}

bool ForwardShadingRenderer::renderOpaque()
{
	IDevice* Device = Engine::GetDevice();
	assert(Device != nullptr);
	Device->Draw();

	return true;
}

bool ForwardShadingRenderer::renderTranslucency()
{
	IDevice* Device = Engine::GetDevice();
	assert(Device != nullptr);
	Device->Draw();

	return true;
}
