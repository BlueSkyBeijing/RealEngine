#pragma once
#include"..\..\..\Frame\Public\RenderTarget.h"
#if WINDOWS_RENDER_DEVICE == USE_VULKAN
#include <SDL.h>
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
	void Update();

protected:
	HWND  RenderWindowHandle;

#if WINDOWS_RENDER_DEVICE == USE_VULKAN
	//GLFWwindow* mMainWindow;
	SDL_Window* mMainWindow;
public:
#endif

};
