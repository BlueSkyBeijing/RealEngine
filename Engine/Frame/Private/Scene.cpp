#include "..\Public\Scene.h"

int Scene::Load()
{
	Camera* MainCamera = new Camera(Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3f(-1.0f, -1.0f, -1.0f), Eigen::Vector3f(0.0f, 0.0f, 1.0f));
	CurrentCamera = MainCamera;
	return 0;
}

ICamera*  Scene::GetCurrentCamera()
{
	return CurrentCamera;
}
