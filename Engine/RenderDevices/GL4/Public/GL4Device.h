#pragma once
#include "..\..\..\Frame\Public\Device.h"
#include "GL4Utility.h"

#include <assert.h>
#include <atlstr.h >
#include <comdef.h>
#include <fstream>
#include <array>

class GL4Device : public IDevice
{
public:
	GL4Device();
	virtual ~GL4Device();

	virtual int Init() override;

	virtual int Draw() override;

protected:

private:
};
