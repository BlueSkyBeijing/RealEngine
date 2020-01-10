#pragma once

#include "..\Public\DeferredShadingRenderer.h"

class LightPrePassShadingRenderer : public DeferredShadingRenderer
{
public:
	LightPrePassShadingRenderer();
	virtual ~LightPrePassShadingRenderer();

	virtual int Render() override;

protected:
	bool renderOpaque();

	bool renderLights();

	bool renderTranslucency();
};
