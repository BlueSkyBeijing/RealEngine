#pragma once

#include "..\Public\DeferredShadingRenderer.h"

class TiledBasedDeferredShadingRenderer : public DeferredShadingRenderer
{
public:
	TiledBasedDeferredShadingRenderer();
	virtual ~TiledBasedDeferredShadingRenderer();

	virtual int Render() override;

protected:
	bool renderOpaque();

	bool renderLights();

	bool renderTranslucency();
};
