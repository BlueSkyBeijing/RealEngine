#pragma once
#include "..\Public\SceneObject.h"
#include "..\Public\Camera.h"

class IScene
{
public:
	virtual int Load() = 0;
	virtual ICamera* GetCurrentCamera() = 0;
};

class Scene : public IScene
{
public:
	virtual int Load() override;
	virtual ICamera* GetCurrentCamera() override;

protected:
	ICamera* CurrentCamera;
};
