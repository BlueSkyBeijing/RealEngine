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

bool LightPrePassShadingRenderer::RenderOpaque()
{
	return true;
}

bool LightPrePassShadingRenderer::RenderLights()
{
	return true;
}

bool LightPrePassShadingRenderer::RenderTranslucency()
{
	return true;
}
