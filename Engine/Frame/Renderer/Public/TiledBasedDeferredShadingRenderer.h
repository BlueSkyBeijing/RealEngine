#pragma once

#include "..\Public\DeferredShadingRenderer.h"

class TiledBasedDeferredShadingRenderer : public DeferredShadingRenderer
{
public:
	TiledBasedDeferredShadingRenderer();
	virtual ~TiledBasedDeferredShadingRenderer();

	virtual int Render() override;

	bool RenderOpaque();

	bool RenderLights();

	bool RenderTranslucency();
};
