#pragma once
#include "..\Public\Scene.h"
#include "..\Renderer\Public\Renderer.h"

class ISceneManager
{
public:
	virtual int Init() = 0;
	virtual int UpdateRenderList(IRenderer* render) = 0;

};


class SceneManager : public ISceneManager
{
public:
	SceneManager(IScene* inScene);
	virtual int Init() override;
	virtual int UpdateRenderList(IRenderer* render) override;
protected:
	IScene* mScene;
};
