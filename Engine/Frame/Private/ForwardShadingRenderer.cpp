#include "..\Public\ForwardShadingRenderer.h"
#include "..\Public\Engine.h"
#include <assert.h>

ForwardShadingRenderer::ForwardShadingRenderer()
{

}

ForwardShadingRenderer::~ForwardShadingRenderer()
{

}

int ForwardShadingRenderer::Render()
{
	IDevice* Device = RealEngine::GetDevice();
	assert(Device != nullptr);
	Device->Draw();

	return 0;
}
