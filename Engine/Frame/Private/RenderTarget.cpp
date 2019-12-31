#include "..\Public\RenderTarget.h"
#include "..\Public\Engine.h"

RenderTarget::RenderTarget():
	Width(1024),
	Height(1024)
{

}

RenderTarget::~RenderTarget()
{

}

int RenderTarget::Init()
{
	return 0;
}

int RenderTarget::UnInit()
{
	return 0;
}

int RenderTarget::GetWidth() const
{
	return Width;
}

int RenderTarget::GetHeight() const
{
	return Height;
}


RenderWindow::RenderWindow()
{

}

RenderWindow::~RenderWindow()
{

}

int RenderWindow::Init()
{
	mWindow = SDL_CreateWindow(
		"Real",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		GetWidth(), GetHeight(),
		0
	);

	return 0;
}

int RenderWindow::UnInit()
{
	SDL_DestroyWindow(mWindow);

	return 0;
}

SDL_Window* RenderWindow::GetWindow() const
{
	return mWindow;
}
