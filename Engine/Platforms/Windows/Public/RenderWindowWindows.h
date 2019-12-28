#pragma once
#include"..\..\..\Frame\Public\RenderTarget.h"
#if WINDOWS_RENDER_DEVICE == USE_VULKAN
#include <GLFW/glfw3.h>
#endif

class RenderWindowWindows : public IRenderTarget
{
public:
	RenderWindowWindows();
	virtual ~RenderWindowWindows();

	virtual int Init() override;
	virtual int GetWidth() const override;
	virtual int GetHeight() const override;

	HWND GetRenderWindowHandle();

protected:
	HWND  RenderWindowHandle;

#if WINDOWS_RENDER_DEVICE == USE_VULKAN
	GLFWwindow* mMainWindow;
public:
	void Update();
#endif

};
