#include "..\Public\TiledForwardShadingRenderer.h"
#include "..\..\Public\Engine.h"
#include <assert.h>

TiledForwardShadingRenderer::TiledForwardShadingRenderer()
{

}

TiledForwardShadingRenderer::~TiledForwardShadingRenderer()
{

}

int TiledForwardShadingRenderer::Render()
{
	IDevice* Device = Engine::GetDevice();
	assert(Device != nullptr);
	Device->Draw();

	return 0;
}

bool TiledForwardShadingRenderer::RenderOpaque()
{
	return true;
}

bool TiledForwardShadingRenderer::RenderTranslucency()
{
	return true;
}
