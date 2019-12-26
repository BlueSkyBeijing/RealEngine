#pragma once

class IRenderer
{
public:
	virtual int Render() = 0;

protected:
	virtual void ComputeVisibility() = 0;
};


class Renderer : public IRenderer
{
public:
	Renderer();
	virtual ~Renderer();

	virtual int Render() override;

protected:
	virtual void ComputeVisibility() override;

};
