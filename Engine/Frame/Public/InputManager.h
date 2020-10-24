#pragma once
#include "Engine.h"

class IRenderer;

class IInputManager
{
public:
	virtual int Init() = 0;

};

class InputManager : public IInputManager
{
public:
	InputManager();
	virtual int Init() override;
protected:
};
