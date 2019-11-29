#pragma once

class IRenderTarget
{
public:
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
};

class RenderTarget : public IRenderTarget
{
public:
	RenderTarget();
	virtual ~RenderTarget();

	virtual int GetWidth() const override;
	virtual int GetHeight() const override;
};
