#include "ForwardShadingCommon.hlsl"

Texture2D DiffuseMap : register(t0);
SamplerState DiffuseSamplerState : register(s0);

float4 PSMain(VertexOut PIn) : SV_Target
{
    //Base color

    //Shadow
    
    //Diffuse BRDF
    
    //Specular BRDF
    
    //Emissive
    
    //Sky light
    
    //Fog

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

    float3 worldNormal = PIn.Normal;
    float3 directionalLightDirection = gDirectionalLightDir;
    float3 reflectionVector = worldNormal;
    float3 cameraVector = gCameraDir;
    float3 DirectionalLightColor = gDirectionalLightColor.rgb;
 
    float NoV = max(0, dot(worldNormal, cameraVector));
    float NoL = max(0, dot(worldNormal, directionalLightDirection));
    float RoL = max(0, dot(reflectionVector, directionalLightDirection));
    float3 H = normalize(cameraVector + directionalLightDirection);
    float NoH = max(0, dot(worldNormal, H));
    float VoH = max(0, dot(cameraVector, H));
    float VoL = max(0, dot(cameraVector, directionalLightDirection));

    BxDFContext context;
    context.NoV = NoV;
    context.NoL = NoL;
    context.VoL = VoL;

	float InvLenH = rsqrt(2 + 2 * context.VoL);
	context.NoH = saturate((context.NoL + context.NoV) * InvLenH);
	context.VoH = saturate(InvLenH + InvLenH * context.VoL);

    SpecularColor = NoL * SpecularGGX(Roughness, SpecularColor, context, NoL);
    //SpecularColor = EnvBRDFApprox(SpecularColor, Roughness, NoV);
    Color += NoL * DirectionalLightColor.rgb * (DiffuseColor + SpecularColor * CalcSpecular(Roughness, RoL, NoH, H, worldNormal));
    Color += SpecularColor * 0.5f;
    Color += Emissive;

    return float4(Color, 1.0f);
}

