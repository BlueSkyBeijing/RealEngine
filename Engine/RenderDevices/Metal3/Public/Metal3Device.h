#pragma once
#include "..\..\..\Frame\Public\Device.h"
#include "Metal3Utility.h"

#include <assert.h>
#include <atlstr.h >
#include <comdef.h>
#include <fstream>
#include <array>

class Metal3Device : public Device
{
public:
	Metal3Device();
	virtual ~Metal3Device();

	virtual int Init() override;
	virtual int UnInit() override;

	virtual int Draw() override;

protected:

private:
};
