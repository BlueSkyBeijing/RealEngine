#include "..\..\..\Frame\Public\RenderTarget.h"
#include "..\..\..\Frame\Public\Engine.h"
#include "..\Public\RenderWindow.h"
#include "..\Public\EngineWindows.h"

RenderWindow::RenderWindow()
{

}

RenderWindow::~RenderWindow()
{

}

int RenderWindow::Initialize()
{
	HINSTANCE  Instacne = EngineWindows::GetInstance()->GetInstanceHandle();
	WNDCLASS WindowClass;
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = 0;
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

	RECT Rectangle = { 0, 0, GetWidth(), GetHeight() };
	AdjustWindowRect(&Rectangle, WS_OVERLAPPEDWINDOW, false);
	int Width = Rectangle.right - Rectangle.left;
	int Height = Rectangle.bottom - Rectangle.top;

	RenderWindowHandle = CreateWindow("Real", "Real",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, Width, Height, 0, 0, Instacne, 0);

	if (!RenderWindowHandle)
	{
		MessageBox(0, "Create window failed.", 0, 0);
		return false;
	}

	ShowWindow(RenderWindowHandle, SW_SHOW);
	UpdateWindow(RenderWindowHandle);

	return 0;
}

int RenderWindow::GetWidth() const
{
	return 1024;
}

int RenderWindow::GetHeight() const
{ 
	return 1024;
}
