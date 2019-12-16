#pragma once

#include "..\Public\Renderer.h"

class DeferredShadingRenderer : public IRenderer
{
public:
	DeferredShadingRenderer();
	virtual ~DeferredShadingRenderer();

	virtual int Render() override;
};
