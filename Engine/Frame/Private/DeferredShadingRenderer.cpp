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
	IDevice* Device = Engine::GetDevice();
	assert(Device != nullptr);
	Device->Draw();

	return 0;
}
