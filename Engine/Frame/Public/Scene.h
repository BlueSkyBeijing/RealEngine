#pragma once
#include "..\Public\SceneObject.h"
#include "..\Public\Camera.h"
#include "..\Public\Light.h"

class IScene
{
public:
	virtual int Load() = 0;
	virtual ICamera* GetCurrentCamera() = 0;
	virtual DirectonalLight* GetMainDirectonalLight() = 0;
};

class Scene : public IScene
{
public:
	virtual int Load() override;
	virtual ICamera* GetCurrentCamera() override;
	virtual DirectonalLight* GetMainDirectonalLight() override;

protected:
	ICamera* mCurrentCamera;
	DirectonalLight* mMainDirectonalLight;
};
