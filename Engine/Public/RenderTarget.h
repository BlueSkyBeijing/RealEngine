#pragma once
#include <windows.h>

class IRenderTarget
{
public:
	virtual int Initialize() = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
};

class RenderTargetWindow : public IRenderTarget
{
public:
	RenderTargetWindow();
	virtual ~RenderTargetWindow();

	virtual int Initialize() override;
	virtual int GetWidth() const override;
	virtual int GetHeight() const override;

protected:
	HWND  RenderWindowHandle;
};
