#include "..\Public\LightPrePassShadingRenderer.h"
#include "..\..\Public\Engine.h"
#include <assert.h>

LightPrePassShadingRenderer::LightPrePassShadingRenderer()
{

}

LightPrePassShadingRenderer::~LightPrePassShadingRenderer()
{

}

int LightPrePassShadingRenderer::Render()
{
	IDevice* Device = Engine::GetDevice();
	assert(Device != nullptr);
	Device->Draw();

	return 0;
}

bool LightPrePassShadingRenderer::renderOpaque()
{
	return true;
}

bool LightPrePassShadingRenderer::renderLights()
{
	return true;
}

bool LightPrePassShadingRenderer::renderTranslucency()
{
	return true;
}
