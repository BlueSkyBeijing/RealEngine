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

	drawRenderables();

	postProcess();

	present();

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
	assert(Engine::GetDevice() != nullptr);
	Engine::GetDevice()->Clear();

	return 0;
}

void Renderer::initView()
{
	computeVisibility();

	initShadow();

	updateUniformBuffer();
}

void Renderer::initShadow()
{
}

void Renderer::updateUniformBuffer()
{
}

void Renderer::computeVisibility()
{
	//check if in the view frustum
	for (size_t i = 0; i < mStaticRenderObjects.size(); i++)
	{
		mVisibilityMap.insert(std::make_pair(mStaticRenderObjects[i], true));
	}

}

void Renderer::createPassConstants()
{
	assert(Engine::GetDevice() != nullptr);
	Engine::GetDevice()->CreatePassConstants();
}

void Renderer::createRenderTarget()
{
	assert(Engine::GetDevice() != nullptr);
	Engine::GetDevice()->CreateRenderTarget();
}

void Renderer::setRenderTarget()
{
	assert(Engine::GetDevice() != nullptr);
	Engine::GetDevice()->SetRenderTarget();
}

void Renderer::setViewPort()
{
	assert(Engine::GetDevice() != nullptr);
	Engine::GetDevice()->SetViewPort();
}

void Renderer::drawRenderables()
{
	assert(Engine::GetDevice() != nullptr);
	for (int i = 0; i < mStaticRenderObjects.size(); i++)
	{
		mStaticRenderObjects[i]->CreateConstants(Engine::GetDevice());
		//per scene object draw
		Engine::GetDevice()->Draw();
	}
}

void Renderer::postProcess()
{
	assert(Engine::GetDevice() != nullptr);
}

void Renderer::present()
{
	assert(Engine::GetDevice() != nullptr);
	Engine::GetDevice()->Present();
}