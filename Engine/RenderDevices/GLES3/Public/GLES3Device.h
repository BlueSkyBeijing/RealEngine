#pragma once
#include "..\..\..\Frame\Public\Device.h"
#include "GLES3Utility.h"

#include <assert.h>
#include <atlstr.h >
#include <comdef.h>
#include <fstream>
#include <array>


class GLES3Device : public IDevice
{
public:
	GLES3Device();
	virtual ~GLES3Device();

	virtual int Init() override;

	virtual int Draw() override;

protected:

private:
};
