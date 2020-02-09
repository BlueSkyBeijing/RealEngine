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
	computeVisibility();

	renderShadowDepth();

	renderOpaque();

	renderTranslucency();

// Postprocessing
// Bloom
// 


	return 0;
}

bool ForwardShadingRenderer::renderShadowDepth()
{
	// Compute visual objects in shadow view

	// Construct shadow view project matrix

	// Set shadow depth render target

	// Clear depth

	// Render depth
	//IDevice* Device = Engine::GetDevice();
	//assert(Device != nullptr);
	//Device->Draw();
	//Device->Present();

	return true;
}

bool ForwardShadingRenderer::renderOpaque()
{
	//IDevice* Device = Engine::GetDevice();
	//assert(Device != nullptr);
	//Device->Draw();
	//Device->Present();

	createPassConstants();

	IDevice* Device = Engine::GetDevice();
	if (Device != nullptr)
	{
		for (int i = 0; i < mStaticRenderObjects.size(); i++)
		{
			mStaticRenderObjects[i]->CreateConstants(Device);
			//per scene object draw
			Device->Draw();
			//final present
			Device->Present();
		}

	}

	return true;
}

bool ForwardShadingRenderer::renderTranslucency()
{
	//IDevice* Device = Engine::GetDevice();
	//assert(Device != nullptr);
	//Device->Draw();
	//Device->Present();

	return true;
}
