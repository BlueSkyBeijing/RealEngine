#pragma once

class ISceneObject
{
public:
	virtual int Load() = 0;
};

class SceneObject : public ISceneObject
{
public:
	virtual int Load();
};
