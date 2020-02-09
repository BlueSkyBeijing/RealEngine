#pragma once
#include "SceneObject.h"

class StaticMeshObject : /*public SceneObject,*/ public Renderable
{
public:
	//virtual int Load() override;
	virtual void CreateConstants(IDevice* device) override;
};

