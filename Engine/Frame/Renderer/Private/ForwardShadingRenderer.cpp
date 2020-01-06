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
	IDevice* Device = Engine::GetDevice();
	assert(Device != nullptr);
	Device->Draw();

	return 0;
}

bool ForwardShadingRenderer::RenderOpaque()
{
	return true;
}

bool ForwardShadingRenderer::RenderTranslucency()
{
	return true;
}
