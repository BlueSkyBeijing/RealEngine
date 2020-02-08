#include "..\Public\SceneObject.h"

void Renderable::createConstants(IDevice* device)
{
	if (device != nullptr)
	{
		device->CreateObjectConstants();
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
