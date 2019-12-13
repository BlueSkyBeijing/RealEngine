
cbuffer CBObject : register(b0)
{
    float4x4 WorldViewProj;
};

struct VertexIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
};

struct VertexOut
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

VertexOut VS(VertexIn VIn)
{
    VertexOut VOut;
	
    VOut.Pos = mul(float4(VIn.Pos, 1.0f), WorldViewProj);
	
    VOut.Color = VIn.Color;
    
    return VOut;
}

float4 PS(VertexOut PIn) : SV_Target
{
    return PIn.Color;
}

