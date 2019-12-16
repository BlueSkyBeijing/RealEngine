#pragma once

#include "..\Public\Renderer.h"

class ForwardShadingRenderer : public IRenderer
{
public:
	ForwardShadingRenderer();
	virtual ~ForwardShadingRenderer();

	virtual int Render() override;
};
