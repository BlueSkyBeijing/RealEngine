#include "ForwardShadingCommon.hlsl"

Texture2D DiffuseMap : register(t0);
SamplerState DiffuseSamplerState : register(s0);

float4 PSMain(VertexOut PIn) : SV_Target
{
    //Base color
    float4 diffuse = DiffuseMap.Sample(DiffuseSamplerState, PIn.TexCoord);

    //Shadow
    
    //Diffuse BRDF
    
    //Specular BRDF
    
    //Emissive
    
    //Sky light
    
    //Fog

    return diffuse;
}

