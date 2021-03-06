#pragma once
#include "Scene.h"
#include "..\Renderer\Public\Renderer.h"
#include "Engine.h"

class IRenderer;

class ISceneManager
{
public:
	virtual int Init() = 0;
    virtual IScene* GetScene() = 0;
	virtual int UpdateRenderList(IRenderer* render) = 0;

};


class SceneManager : public ISceneManager
{
public:
	SceneManager(IScene* inScene);
	virtual int Init() override;
    virtual IScene* GetScene() override;
	virtual int UpdateRenderList(IRenderer* render) override;
protected:
	IScene* mScene;
};
