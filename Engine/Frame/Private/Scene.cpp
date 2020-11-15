#include "..\Public\Scene.h"
#include "..\Public\StaticMeshObject.h"
#include "..\..\OpenFBX\ofbx.h"

int Scene::Load()
{
	Camera* mainCamera = new Camera(Eigen::Vector3f(0.0f, 5.0f, 5.0f), Eigen::Vector3f(0.0f, -1.0f, -1.0f), Eigen::Vector3f(0.0f, 1.0f, 0.0f));
	mCurrentCamera = mainCamera;
	DirectonalLight* directonalLight = new DirectonalLight();
	directonalLight->SetDirection(Eigen::Vector3f(-1.0f, -1.0f, -1.0f));
	directonalLight->SetColor(Eigen::Vector3f(1.0f, 1.0f, 1.0f));
	mMainDirectonalLight = directonalLight;

	IRenderable* testObj = new StaticMeshObject;
	mSceneObjects.push_back((ISceneObject*)testObj);

	FILE* fp;
	errno_t err = fopen_s(&fp, "test.fbx", "rb");
    if (!fp) return 0;

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    auto* content = new ofbx::u8[file_size];
    fread(content, 1, file_size, fp);
	ofbx::IScene* scene = ofbx::load((ofbx::u8*)content, file_size, (ofbx::u64)ofbx::LoadFlags::TRIANGULATE);
	if (!scene) 
	{
		OutputDebugString(ofbx::getError());
	}
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
