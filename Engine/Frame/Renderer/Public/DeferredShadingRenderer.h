#pragma once

#include "..\Public\Renderer.h"

class DeferredShadingRenderer : public Renderer
{
public:
	DeferredShadingRenderer();
	virtual ~DeferredShadingRenderer();

	virtual int Render() override;

protected:
	bool renderOpaque();

	bool renderLights();

	bool renderTranslucency();
};
