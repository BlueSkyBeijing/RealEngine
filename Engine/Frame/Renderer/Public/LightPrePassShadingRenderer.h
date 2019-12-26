#pragma once

#include "..\Public\DeferredShadingRenderer.h"

class LightPrePassShadingRenderer : public DeferredShadingRenderer
{
public:
	LightPrePassShadingRenderer();
	virtual ~LightPrePassShadingRenderer();

	virtual int Render() override;

	bool RenderOpaquePass();

	bool RenderLights();

	bool RenderTranslucency();
};
