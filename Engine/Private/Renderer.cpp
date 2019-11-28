#include "..\Public\Renderer.h"
#include "..\Public\Engine.h"
#include <assert.h>

RealRenderer::RealRenderer()
{

}

RealRenderer::~RealRenderer()
{

}

int RealRenderer::Render()
{
	IDevice* Device = RealEngine::GetInstance()->GetDevice();
	assert(Device != nullptr);
	Device->Draw();

	return 0;
}
