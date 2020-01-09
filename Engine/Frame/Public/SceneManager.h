#pragma once

class ISceneManager
{
public:
	virtual int Init() = 0;
};


class SceneManager : public ISceneManager
{
public:
	virtual int Init() override;
};
