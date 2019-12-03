#pragma once
#include"..\..\..\Frame\Public\RenderTarget.h"

class RenderWindowWindows : public IRenderTarget
{
public:
	RenderWindowWindows();
	virtual ~RenderWindowWindows();

	virtual int Init() override;
	virtual int GetWidth() const override;
	virtual int GetHeight() const override;

protected:
	HWND  RenderWindowHandle;
};
