#include "..\..\..\Frame\Public\RenderTarget.h"
#include "..\..\..\Frame\Public\Engine.h"
#include "..\Public\RenderWindowWindows.h"
#include "..\Public\EngineWindows.h"
#include "..\..\..\Frame\Public\Globals.h"

#if WINDOWS_RENDER_DEVICE == USE_VULKAN
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#endif


LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return EngineWindows::GetInstance()->MessageProcess(hwnd, msg, wParam, lParam);
}

RenderWindowWindows::RenderWindowWindows()
{

}

RenderWindowWindows::~RenderWindowWindows()
{

}

int RenderWindowWindows::Init()
{
#if WINDOWS_RENDER_DEVICE == USE_DX12
	HINSTANCE  Instacne = EngineWindows::GetInstance()->GetInstanceHandle();

	WNDCLASS WindowClass;
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = MainWndProc;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = Instacne;
	WindowClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	WindowClass.hCursor = LoadCursor(0, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	WindowClass.lpszMenuName = 0;
	WindowClass.lpszClassName = "Real";

	if (!RegisterClass(&WindowClass))
	{
		MessageBox(0, "Register class failed.", 0, 0);

		return 1;
	}

	RenderWindowHandle = CreateWindow("Real", "Real",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, GetWidth(), GetHeight(), 0, 0, Instacne, 0);

	if (!RenderWindowHandle)
	{
		MessageBox(0, "Create window failed.", 0, 0);
		return false;
	}

	ShowWindow(RenderWindowHandle, SW_SHOW);
	UpdateWindow(RenderWindowHandle);

#else
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	mMainWindow = glfwCreateWindow(GetWidth(), GetHeight(), "Real", nullptr, nullptr);
#endif

	return 0;
}

int RenderWindowWindows::GetWidth() const
{
	return 1024;
}

int RenderWindowWindows::GetHeight() const
{ 
	return 768;
}

HWND RenderWindowWindows::GetRenderWindowHandle()
{
	return RenderWindowHandle;
}

#if WINDOWS_RENDER_DEVICE == USE_VULKAN
void RenderWindowWindows::Update()
{
	if (glfwWindowShouldClose(mMainWindow))
	{
		GExit = true;
		glfwDestroyWindow(mMainWindow);
		glfwTerminate();
	}
	else
	{
		glfwPollEvents();
	}
}
#endif
