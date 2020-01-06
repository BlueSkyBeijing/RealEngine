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

bool TiledBasedDeferredShadingRenderer::RenderOpaque()
{
	return true;
}

bool TiledBasedDeferredShadingRenderer::RenderLights()
{
	return true;
}

bool TiledBasedDeferredShadingRenderer::RenderTranslucency()
{
	return true;
}
