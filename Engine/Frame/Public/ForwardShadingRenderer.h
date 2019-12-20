#pragma once

#include "..\Public\Renderer.h"

class ForwardShadingRenderer : public Renderer
{
public:
	ForwardShadingRenderer();
	virtual ~ForwardShadingRenderer();

	virtual int Render() override;
};
