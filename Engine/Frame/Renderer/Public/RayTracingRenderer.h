#pragma once

#include "..\Public\Renderer.h"

class RayTracingRenderer : public Renderer
{
public:
	RayTracingRenderer();
	virtual ~RayTracingRenderer();

	virtual int Render() override;

protected:
	bool renderOpaque();

	bool renderTranslucency();
};
