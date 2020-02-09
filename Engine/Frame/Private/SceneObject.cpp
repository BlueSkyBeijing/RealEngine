#include "..\Public\SceneObject.h"

void Renderable::CreateConstants(IDevice* device)
{
	if (device != nullptr)
	{
		device->CreateObjectConstants();
		device->CreateMaterialConstants();
	}
}

int SceneObject::Load()
{
	return 0;
}

Eigen::Vector3f SceneObject::GetPosition()
{
	return Position;
}

Eigen::Vector3f SceneObject::GetRotation()
{
	return Rotation;
}
