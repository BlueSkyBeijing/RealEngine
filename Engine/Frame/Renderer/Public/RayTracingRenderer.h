#pragma once

#include "..\Public\Renderer.h"

class RayTracingRenderer : public Renderer
{
public:
	RayTracingRenderer();
	virtual ~RayTracingRenderer();

	virtual int Render() override;

	bool RenderOpaquePass();

	bool RenderTranslucency();
};
