#pragma once
#include "..\..\Utility\Public\Math.h"

class ILight
{
public:
	virtual Vector3 GetPosition() = 0;
	virtual Vector3 GetDirection() = 0;
};

