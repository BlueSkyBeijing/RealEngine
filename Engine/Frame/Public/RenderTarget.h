#pragma once

class IRenderTarget
{
public:
	virtual int Initialize() = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
};
