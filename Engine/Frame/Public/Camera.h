#pragma once
#include "..\..\Utility\Public\Math.h"

class ICamera
{
public:
	virtual Vector3 GetPosition() = 0;
	virtual Vector3 GetDirection() = 0;
	virtual Vector3 GetUp() = 0;
};

