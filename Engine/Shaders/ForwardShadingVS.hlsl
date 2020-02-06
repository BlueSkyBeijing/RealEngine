#include "ForwardShadingCommon.hlsl"

VertexOut VSMain(VertexIn VIn)
{
    VertexOut VOut;
	
    float4x4 WorldViewProj = mul(gWorld, gViewProj);
    VOut.Pos = mul(float4(VIn.Pos, 1.0f), WorldViewProj);
	
    VOut.Color = VIn.Color;
 
    VOut.TexCoord = VIn.TexCoord;

    return VOut;
}