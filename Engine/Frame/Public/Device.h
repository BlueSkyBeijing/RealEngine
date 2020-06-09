#pragma once
#include "Engine.h"

class ISamplerState
{
};

class IRasterizerState
{
};

class IDepthStencilState
{
};

class IBlendState
{
};

class IDevice
{
public:
	virtual int Init() = 0;
	virtual int UnInit() = 0;
	virtual int Clear() = 0; 
	virtual IRenderTarget* CreateRenderTarget() = 0;
	virtual int SetRenderTarget(IRenderTarget* rt) = 0;
	virtual int SetViewPort() = 0;
	virtual int SetPipelineState() = 0;
	virtual int Draw() = 0; 
	virtual int Present() = 0;
	virtual int CreateObjectConstants() = 0;
	virtual int CreateMaterialConstants() = 0;
	virtual int CreatePassConstants() = 0;

};

class Device : public IDevice
{
public:
	virtual int Init() override;
	virtual int UnInit() override;
	virtual int Clear() override;
	virtual IRenderTarget* CreateRenderTarget() override;;
	virtual int SetRenderTarget(IRenderTarget* rt) override;
	virtual int SetViewPort() override;
	virtual int SetPipelineState() override;
	virtual int Draw() override; 
	virtual int Present() override;
	virtual int CreateObjectConstants() override;
	virtual int CreateMaterialConstants() override;
	virtual int CreatePassConstants() override;

};

