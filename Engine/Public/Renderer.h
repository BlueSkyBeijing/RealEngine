#pragma once

class IRenderer
{
public:
	virtual int Render() = 0;
};


class RealRenderer : public IRenderer
{
public:
	RealRenderer();
	virtual ~RealRenderer();

	virtual int Render() override;
};
