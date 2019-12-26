#pragma once

#include "..\Public\DeferredShadingRenderer.h"

class TiledBasedDeferredShadingRenderer : public DeferredShadingRenderer
{
public:
	TiledBasedDeferredShadingRenderer();
	virtual ~TiledBasedDeferredShadingRenderer();

	virtual int Render() override;

	bool RenderOpaquePass();

	bool RenderLights();

	bool RenderTranslucency();
};
