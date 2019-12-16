#include "..\Public\DeferredShadingRenderer.h"
#include "..\Public\Engine.h"
#include <assert.h>

DeferredShadingRenderer::DeferredShadingRenderer()
{

}

DeferredShadingRenderer::~DeferredShadingRenderer()
{

}

int DeferredShadingRenderer::Render()
{
	IDevice* Device = RealEngine::GetDevice();
	assert(Device != nullptr);
	Device->Draw();

	return 0;
}
