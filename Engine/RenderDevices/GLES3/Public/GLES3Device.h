#pragma once
#include "..\..\..\Frame\Public\Device.h"
#include "GLES3Utility.h"

#include <assert.h>
#include <comdef.h>
#include <fstream>
#include <array>


class GLES3Device : public Device
{
public:
	GLES3Device();
	virtual ~GLES3Device();

	virtual int Init() override;
	virtual int UnInit() override;

	virtual int Draw() override;

protected:

private:
};
