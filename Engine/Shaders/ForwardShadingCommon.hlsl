#include "ShadingCommon.hlsl"

struct VertexIn
{
    float3 Pos : POSITION;
    float3 Normal : NORMAL;
    float2 TexCoord : TEXCOORD;
};

struct VertexOut
{
    float4 Pos : SV_POSITION;
    float3 Normal : NORMAL;
    float2 TexCoord : TEXCOORD;
};

cbuffer cbObject : register(b0)
{
    float4x4 gWorld;
};

cbuffer cbMaterial : register(b1)
{
    float4 gBaseColor;
    float4 gEmissiveColor;
    float gSpecular;
    float gMetallic;
    float gRoughness;
};

cbuffer cbPass : register(b2)
{
    float4x4 gView;
    float4x4 gProj;
    float4x4 gViewProj;
    float3 gCameraPos;
    float3 gCameraDir;
    float3 gDirectionalLightDir;
    float4 gDirectionalLightColor;
};

