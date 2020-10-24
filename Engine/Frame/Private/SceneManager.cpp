#include "..\Public\SceneManager.h"

SceneManager::SceneManager(IScene* inScene):
	mScene(inScene)
{

}

int SceneManager::Init()
{
	return 0;
}

IScene* SceneManager::GetScene()
{
	return mScene;
}

int SceneManager::UpdateRenderList(IRenderer* render)
{
	render->UpdateRenderList(mScene);
	return 0;
}
