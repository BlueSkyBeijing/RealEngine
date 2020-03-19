#pragma once
#include <SDL.h>

class IRenderTarget
{
public:
	virtual int Init() = 0;
	virtual int UnInit() = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
};

class RenderTarget : public IRenderTarget
{
public:
	RenderTarget();
	virtual ~RenderTarget();

	virtual int Init() override;
	virtual int UnInit() override;
	virtual int GetWidth() const override;
	virtual int GetHeight() const override;

protected:
	int Width;
	int Height;
};

class RenderWindow : public RenderTarget
{
public:
	RenderWindow();
	virtual ~RenderWindow();

	virtual int Init() override;
	virtual int UnInit() override;

	virtual int OnResize();

	SDL_Window* GetWindow() const;

protected:
	SDL_Window* mWindow;
};
