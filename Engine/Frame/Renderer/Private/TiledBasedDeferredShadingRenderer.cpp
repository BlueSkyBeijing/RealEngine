#include "..\Public\TiledBasedDeferredShadingRenderer.h"
#include "..\..\Public\Engine.h"
#include <assert.h>

TiledBasedDeferredShadingRenderer::TiledBasedDeferredShadingRenderer()
{

}

TiledBasedDeferredShadingRenderer::~TiledBasedDeferredShadingRenderer()
{

}

int TiledBasedDeferredShadingRenderer::Render()
{
	IDevice* Device = Engine::GetDevice();
	assert(Device != nullptr);
	Device->Draw();

	return 0;
}

bool TiledBasedDeferredShadingRenderer::renderOpaque()
{
	return true;
}

bool TiledBasedDeferredShadingRenderer::renderLights()
{
	return true;
}

bool TiledBasedDeferredShadingRenderer::renderTranslucency()
{
	return true;
}
