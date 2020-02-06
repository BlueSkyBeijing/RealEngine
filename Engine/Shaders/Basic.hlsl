#include "LightingModel.hlsl"

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
    float3 gEyePosW;
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
	
    float4x4 WorldViewProj = mul(gWorld, gViewProj);
    VOut.Pos = mul(float4(VIn.Pos, 1.0f), WorldViewProj);
	
    VOut.Color = VIn.Color;
 
    VOut.TexCoord = VIn.TexCoord;

    return VOut;
}

float4 PSMain(VertexOut PIn) : SV_Target
{
    float3 Color = 0;

    float Opacity = 1.0f;
    float3 BaseColor = gBaseColor.rgb;
    float Metallic = gMetallic;
    float Specular = gSpecular;
    float Roughness = gRoughness;
    float3 Emissive = gEmissiveColor.rgb;

    float4 diffuse = DiffuseMap.Sample(DiffuseSamplerState, PIn.TexCoord);

    BaseColor = diffuse.rgb;
    
    float DielectricSpecular = 0.08 * Specular;
    float3 DiffuseColor = BaseColor - BaseColor * Metallic; // 1 mad
    float3 SpecularColor = (DielectricSpecular - DielectricSpecular * Metallic) + BaseColor * Metallic; // 2 mad

    float3 worldNormal = float3(0.0f, 1.0f, 0.0f);
    float3 directionalLightDirection = float3(-1.0f, -1.0f, -1.0f);
    float3 reflectionVector = float3(0.0f, 1.0f, 0.0f);
    float3 cameraVector = float3(-1.0f, 0.0f, 0.0f);
    float3 DirectionalLightColor = float3(1.0f, 1.0f, 1.0f);
 
    float NoV = max(0, dot(worldNormal, cameraVector));
    float NoL = max(0, dot(worldNormal, directionalLightDirection));
    float RoL = max(0, dot(reflectionVector, directionalLightDirection));
    float3 H = normalize(cameraVector + directionalLightDirection);
    float NoH = max(0, dot(worldNormal, H));
    
    SpecularColor = EnvBRDFApprox(SpecularColor, Roughness, NoV);
    Color += NoL * DirectionalLightColor.rgb * (DiffuseColor + SpecularColor * CalcSpecular(Roughness, RoL, NoH, H, worldNormal));
    Color += SpecularColor;
    Color += Emissive;

    return float4(Color, 1.0f);
}

