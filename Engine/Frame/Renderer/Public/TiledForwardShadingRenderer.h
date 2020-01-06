#pragma once

#include "..\Public\ForwardShadingRenderer.h"

class TiledForwardShadingRenderer : public ForwardShadingRenderer
{
public:
	TiledForwardShadingRenderer();
	virtual ~TiledForwardShadingRenderer();

	virtual int Render() override;

	bool RenderOpaque();

	bool RenderTranslucency();
};
