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

enum CompareFunction
{
	CF_Less,
	CF_LessEqual,
	CF_Greater,
	CF_GreaterEqual,
	CF_Equal,
	CF_NotEqual,
	CF_Never,
	CF_Always,
	ECompareFunction_Num,
};

enum BlendOperation
{
	BO_Add,
	BO_Subtract,
	BO_Min,
	BO_Max,
	BO_ReverseSubtract,

	EBlendOperation_Num,
};

enum StencilOp
{
	SO_Keep,
	SO_Zero,
	SO_Replace,
	SO_SaturatedIncrement,
	SO_SaturatedDecrement,
	SO_Invert,
	SO_Increment,
	SO_Decrement,

	EStencilOp_Num,
};

enum BlendFactor
{
	BF_Zero,
	BF_One,
	BF_SourceColor,
	BF_InverseSourceColor,
	BF_SourceAlpha,
	BF_InverseSourceAlpha,
	BF_DestAlpha,
	BF_InverseDestAlpha,
	BF_DestColor,
	BF_InverseDestColor,
	BF_ConstantBlendFactor,
	BF_InverseConstantBlendFactor,

	EBlendFactor_Num,
};

enum UniformBufferBaseType
{
	UBMT_INVALID,
	UBMT_BOOL,
	UBMT_INT32,
	UBMT_UINT32,
	UBMT_FLOAT32,
	UBMT_STRUCT,
	UBMT_SRV,
	UBMT_UAV,
	UBMT_SAMPLER,
	UBMT_TEXTURE,

	EUniformBufferBaseType_Num,
};

enum PrimitiveType
{
	// Topology that defines a triangle N with 3 vertex extremities: 3*N+0, 3*N+1, 3*N+2.
	PT_TriangleList,

	// Topology that defines a triangle N with 3 vertex extremities: N+0, N+1, N+2.
	PT_TriangleStrip,

	// Topology that defines a line with 2 vertex extremities: 2*N+0, 2*N+1.
	PT_LineList,

	// Topology that defines a quad N with 4 vertex extremities: 4*N+0, 4*N+1, 4*N+2, 4*N+3.
	// Supported only if GRHISupportsQuadTopology == true.
	PT_QuadList,

	// Topology that defines a point N with a single vertex N.
	PT_PointList,

	// Topology that defines a screen aligned rectangle N with only 3 vertex corners:
	//    3*N + 0 is upper-left corner,
	//    3*N + 1 is upper-right corner,
	//    3*N + 2 is the lower-left corner.
	// Supported only if GRHISupportsRectTopology == true.
	PT_RectList,
	PT_Num,
};

class ICommandList
{
public:
	virtual int Clear() = 0;
	virtual int SetRenderTarget(IRenderTarget* rt) = 0;
	virtual int SetViewPort() = 0;
	virtual int SetPipelineState() = 0;
	virtual int Draw() = 0;
};

class CommandListExecutor
{
public:
	void ExecuteList(ICommandList& CmdList);
};

class ICommandContext
{
	virtual void DrawPrimitive(uint32 PrimitiveType, uint32 BaseVertexIndex, uint32 NumPrimitives, uint32 NumInstances) = 0;
	virtual void BeginRenderPass() = 0;
	virtual void EndRenderPass() = 0;
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

