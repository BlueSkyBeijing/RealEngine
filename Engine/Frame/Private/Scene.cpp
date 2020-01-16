#include "..\Public\Scene.h"

int Scene::Load()
{
	Camera* mainCamera = new Camera(Eigen::Vector3f(5.0f, 5.0f, 5.0f), Eigen::Vector3f(-1.0f, -1.0f, -1.0f), Eigen::Vector3f(0.0f, 0.0f, 1.0f));
	CurrentCamera = mainCamera;
	DirectonalLight* directonalLight = new DirectonalLight();
	directonalLight->SetDirection(Eigen::Vector3f(-1.0f, -1.0f, -1.0f));
	MainDirectonalLight = directonalLight;
	return 0;
}

ICamera*  Scene::GetCurrentCamera()
{
	return CurrentCamera;
}
