#pragma once
#include "Light.h"
#include <vector>
#include "Engine.h"

class ICamera;
class ISceneObject;

class IScene
{
public:
	virtual int Load() = 0;
	virtual ICamera* GetCurrentCamera() = 0;
	virtual DirectonalLight* GetMainDirectonalLight() = 0;
	virtual const std::vector<ISceneObject*> GetSceneObjects() const = 0;
};

class Scene : public IScene
{
public:
	virtual int Load() override;
	virtual ICamera* GetCurrentCamera() override;
	virtual DirectonalLight* GetMainDirectonalLight() override;
	virtual const std::vector<ISceneObject*> GetSceneObjects() const override;

protected:
	ICamera* mCurrentCamera;
	DirectonalLight* mMainDirectonalLight;
	std::vector<ISceneObject*> mSceneObjects;

};
