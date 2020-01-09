#pragma once
#include "SceneObject.h"

class IScene
{
public:
	virtual int Load() = 0;
};

class Scene : public IScene
{
public:
	virtual int Load() override;
};
