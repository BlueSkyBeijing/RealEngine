#pragma once

class IRenderTarget
{
public:
	virtual int Init() = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
};
