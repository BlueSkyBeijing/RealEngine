#pragma once
#include "..\..\Public\SceneObject.h"
#include <vector>
#include <map>
#include "..\..\Public\Engine.h"
#include "..\..\Public\PostProcessing.h"

class IRenderable;
class IScene;

class IRenderCommand
{
public:
    virtual void Execut() = 0;

protected:
};

template<typename TCmd>
class RenderCommand : public IRenderCommand
{
public:
    IRenderCommand* mNext = nullptr;
    virtual void Execut() override
	{
        TCmd* ThisCmd = static_cast<TCmd*>(this);
        ThisCmd->Execute();
        ThisCmd->~TCmd();
	}

protected:
};

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

class IRenderCommandExecutor
{
public:
    virtual int GetCommandList() = 0;
	virtual void ExecuteList(IRenderCommandList& cmdList) = 0;

protected:
};

class RenderCommandExecutor : public IRenderCommandExecutor
{
public:
    virtual int GetCommandList() override;
    virtual void ExecuteList(IRenderCommandList& cmdList) override;

protected:
};

class RenderCommandSetShaderParameter final : public RenderCommand<RenderCommandSetShaderParameter>
{
public:
	RenderCommandSetShaderParameter()
    {
    }
    void Execute();
};


class IRenderer
{
public:
	virtual int Render() = 0;
	virtual int UpdateRenderList(IScene* scene) = 0;

protected:
	virtual int clear() = 0;
	virtual void initView() = 0;
	virtual void initShadow() = 0;
	virtual void initShadowVisibility() = 0;
	virtual void gatherShadowPrimitives() = 0;
	virtual void createShadowDepthTargets() = 0;
	virtual void updateUniformBuffer() = 0;
	virtual void computeVisibility() = 0;
	virtual void createPassConstants() = 0;
	virtual void createRenderTarget() = 0;
	virtual void setRenderTarget() = 0;
	virtual void setViewPort() = 0;
	virtual void drawRenderables() = 0;
	virtual void postProcess() = 0;
	virtual void present() = 0;

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
	virtual void initView() override;
	virtual void initShadow() override;
	virtual void initShadowVisibility() override;
	virtual void gatherShadowPrimitives() override;
	virtual void createShadowDepthTargets() override;
	virtual void computeVisibility() override;
	virtual void createPassConstants() override;
	virtual void updateUniformBuffer() override;
	virtual void createRenderTarget() override;
	virtual void setRenderTarget() override;
	virtual void setViewPort() override;
	virtual void drawRenderables() override;
	virtual void postProcess() override;
	virtual void present() override;

protected:
	std::vector<IRenderable*> mStaticRenderObjects;
	std::map<IRenderable*, bool> mVisibilityMap;
	IPostProcessing* mPostProcessing;
};
