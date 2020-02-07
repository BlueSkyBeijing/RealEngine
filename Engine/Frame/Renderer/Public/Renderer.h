#pragma once
#include "..\..\Public\SceneObject.h"
#include "..\..\Public\Scene.h"
#include <vector>

class IRenderCommandList
{
public:
	virtual int Flush() = 0;

protected:
	virtual int reset() = 0;
};

class RenderCommandList : public IRenderCommandList
{
public:
	virtual int Flush() override;

protected:
	virtual int reset() override;
};

class IRenderer
{
public:
	virtual int Render() = 0;
	virtual int UpdateRenderList(IScene* scene) = 0;

protected:
	virtual int clear() = 0;
	virtual void computeVisibility() = 0;
	virtual void createPassConstants() = 0;

};


class Renderer : public IRenderer
{
public:
	Renderer();
	virtual ~Renderer();

	virtual int Render() override;
	virtual int UpdateRenderList(IScene* scene) override;

protected:
	virtual int clear() override;
	virtual void computeVisibility() override;
	virtual void createPassConstants() override;
protected:
	std::vector<IRenderable*> mStaticRenderObjects;
};
