#include "..\Public\Renderer.h"
#include "..\..\Public\Engine.h"
#include <assert.h>


int RenderCommandList::Flush()
{
	return 0;
}

int RenderCommandList::reset()
{
	return 0;
}

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

int Renderer::Render()
{
	clear();

	computeVisibility();

	createPassConstants();

	IDevice* Device = Engine::GetDevice();
	if (Device != nullptr)
	{	
		for (int i = 0; i < mStaticRenderObjects.size(); i++)
		{
			mStaticRenderObjects[i]->createConstants(Device);
			//per scene object draw
			Device->Draw();
		}

		//final present
		Device->Present();
	}

	return 0;
}

int Renderer::UpdateRenderList(IScene* scene)
{
	mStaticRenderObjects.clear();
	for (size_t i = 0; i < scene->GetSceneObjects().size(); i++)
	{
		mStaticRenderObjects.push_back((IRenderable*)scene->GetSceneObjects()[i]);
	}
	return 0;
}

int Renderer::clear()
{
	return 0;
}

void Renderer::computeVisibility()
{

}

void Renderer::createPassConstants()
{
	IDevice* Device = Engine::GetDevice();
	if (Device != nullptr)
	{
	}
}
