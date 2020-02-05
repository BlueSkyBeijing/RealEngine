
cbuffer cbObject : register(b0)
{
    float4x4 gWorld;
};

cbuffer cbPass : register(b1)
{
    float4x4 gView;
    float4x4 gProj;
    float4x4 gViewProj;
    float3 gEyePosW;
};

cbuffer cbMaterial : register(b2)
{
    float4 gBaseColor;
    float4 gEmissiveColor;
    float gSpecular;
    float gMetallic;
    float gRoughness;
};

cbuffer CBObject : register(b0)
{
    float4x4 WorldViewProj;
};

struct VertexIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 TexCoord : TEXCOORD;
};

struct VertexOut
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
    float2 TexCoord : TEXCOORD;
};

Texture2D DiffuseMap : register(t0);
SamplerState DiffuseSamplerState : register(s0);

VertexOut VSMain(VertexIn VIn)
{
    VertexOut VOut;
	
    VOut.Pos = mul(float4(VIn.Pos, 1.0f), WorldViewProj);
	
    VOut.Color = VIn.Color;
 
    VOut.TexCoord = VIn.TexCoord;

    return VOut;
}

float4 PSMain(VertexOut PIn) : SV_Target
{
    float4 diffuse = DiffuseMap.Sample(DiffuseSamplerState, PIn.TexCoord);

    return diffuse;
}

