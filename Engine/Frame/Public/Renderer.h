#pragma once

class IRenderer
{
public:
	virtual int Render() = 0;
};


class Renderer : public IRenderer
{
public:
	Renderer();
	virtual ~Renderer();

	virtual int Render() override;
};
