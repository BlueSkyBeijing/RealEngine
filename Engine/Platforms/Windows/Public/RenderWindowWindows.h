#pragma once
#include"..\..\..\Frame\Public\RenderTarget.h"

class RenderWindowWindows : public RenderWindow
{
public:
	RenderWindowWindows();
	virtual ~RenderWindowWindows();

	virtual int Init() override;

	HWND GetRenderWindowHandle();

protected:
	HWND  RenderWindowHandle;
};
