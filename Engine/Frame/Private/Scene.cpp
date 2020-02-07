#include "..\Public\Scene.h"
#include "..\Public\StaticMeshObject.h"

int Scene::Load()
{
	Camera* mainCamera = new Camera(Eigen::Vector3f(0.0f, 5.0f, 5.0f), Eigen::Vector3f(0.0f, -1.0f, -1.0f), Eigen::Vector3f(0.0f, 1.0f, 0.0f));
	mCurrentCamera = mainCamera;
	DirectonalLight* directonalLight = new DirectonalLight();
	directonalLight->SetDirection(Eigen::Vector3f(-1.0f, -1.0f, -1.0f));
	directonalLight->SetColor(Eigen::Vector3f(1.0f, 1.0f, 1.0f));
	mMainDirectonalLight = directonalLight;

	ISceneObject* testObj = new StaticMeshObject;
	mSceneObjects.push_back(testObj);
	return 0;
}

ICamera*  Scene::GetCurrentCamera()
{
	return mCurrentCamera;
}

DirectonalLight* Scene::GetMainDirectonalLight()
{
	return mMainDirectonalLight;
}

const std::vector<ISceneObject*> Scene::GetSceneObjects() const
{
	return mSceneObjects;
}
