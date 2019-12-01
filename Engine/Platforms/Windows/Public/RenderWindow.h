#pragma once
#include"..\..\..\Frame\Public\RenderTarget.h"

class RenderWindow : public IRenderTarget
{
public:
	RenderWindow();
	virtual ~RenderWindow();

	virtual int Initialize() override;
	virtual int GetWidth() const override;
	virtual int GetHeight() const override;

protected:
	HWND  RenderWindowHandle;
};
