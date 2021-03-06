#include "Common.hlsl"


//Diffuse Light
//Lambert

float3 Lambert(float3 normal, float3 lightDir, float3 lightColor)
{
    float NdotL = max(0.0, dot(normal, lightDir));
    return lightColor * NdotL;
}

//float-Lambert

float3 floatLambert(float3 normal, float3 lightDir, float3 lightColor)
{
    float NdotL = max(0.0, dot(normal, lightDir));
    float floatLambertDiffuse = pow(NdotL * 0.5 + 0.5, 2.0);
    return lightColor * floatLambertDiffuse;
}


// Specular
// Phong

float3 Phong(float3 normal, float3 lightDir, float3 lightColor, float3 specularColor, float specPower, float3 viewDir)
{
    float NdotL = max(0, dot(normal, lightDir));
	 
    float3 lightReflectDirection = reflect(-lightDir, normal);
    float RdotV = max(0, dot(lightReflectDirection, viewDir));
    float3 spec = pow(RdotV, specPower / 4) * specularColor;
    return lightColor.rgb * NdotL + lightColor.rgb * specularColor.rgb * spec;
}

// Blinn-Phong

float3 BlinnPhong(float3 normal, float3 lightDir, float3 lightColor, float3 specularColor, float specPower, float3 viewDir)
{
    float NdotL = max(0, dot(normal, lightDir));
	 
    float3 floatVector = normalize(lightDir + viewDir);
    float NdotH = max(0, dot(normal, floatVector));
    float3 spec = pow(NdotH, specPower) * specularColor;
	 
    return lightColor.rgb * NdotL + lightColor.rgb * specularColor.rgb * spec;
}

// BRDF
// Empirical Models
// Data-driven Models
// Physical-based Models

// Diffuse BRDF
// Lambert

// Specular BRDF
// Cook-Torrance BRDF

// Specular distribution
// Trowbridge-Reitz (GGX)

// Geometric shadowing
// Schlick

// Fresnel
// Schlick


// Environment BRDF



// Helmholtz Recoprpcity Rule

// Physically based shading model
// parameterized with the below options

// Microfacet specular = D*G*F / (4*NoL*NoV) = D*Vis*F
// Vis = G / (4*NoL*NoV)

float3 Diffuse_Lambert(float3 DiffuseColor)
{
    return DiffuseColor * (1 / PI);
}

// [Burley 2012, "Physically-Based Shading at Disney"]
float3 Diffuse_Burley(float3 DiffuseColor, float Roughness, float NoV, float NoL, float VoH)
{
    float FD90 = 0.5 + 2 * VoH * VoH * Roughness;
    float FdV = 1 + (FD90 - 1) * Pow5(1 - NoV);
    float FdL = 1 + (FD90 - 1) * Pow5(1 - NoL);
    return DiffuseColor * ((1 / PI) * FdV * FdL);
}

// [Gotanda 2012, "Beyond a Simple Physically Based Blinn-Phong Model in Real-Time"]
float3 Diffuse_OrenNayar(float3 DiffuseColor, float Roughness, float NoV, float NoL, float VoH)
{
    float a = Roughness * Roughness;
    float s = a; // / ( 1.29 + 0.5 * a );
    float s2 = s * s;
    float VoL = 2 * VoH * VoH - 1; // double angle identity
    float Cosri = VoL - NoV * NoL;
    float C1 = 1 - 0.5 * s2 / (s2 + 0.33);
    float C2 = 0.45 * s2 / (s2 + 0.09) * Cosri * (Cosri >= 0 ? rcp(max(NoL, NoV)) : 1);
    return DiffuseColor / PI * (C1 + C2) * (1 + Roughness * 0.5);
}

// [Gotanda 2014, "Designing Reflectance Models for New Consoles"]
float3 Diffuse_Gotanda(float3 DiffuseColor, float Roughness, float NoV, float NoL, float VoH)
{
    float a = Roughness * Roughness;
    float a2 = a * a;
    float F0 = 0.04;
    float VoL = 2 * VoH * VoH - 1; // double angle identity
    float Cosri = VoL - NoV * NoL;
#if 1
    float a2_13 = a2 + 1.36053;
    float Fr = (1 - (0.542026 * a2 + 0.303573 * a) / a2_13) * (1 - pow(1 - NoV, 5 - 4 * a2) / a2_13) * ((-0.733996 * a2 * a + 1.50912 * a2 - 1.16402 * a) * pow(1 - NoV, 1 + rcp(39 * a2 * a2 + 1)) + 1);
	//float Fr = ( 1 - 0.36 * a ) * ( 1 - pow( 1 - NoV, 5 - 4*a2 ) / a2_13 ) * ( -2.5 * Roughness * ( 1 - NoV ) + 1 );
    float Lm = (max(1 - 2 * a, 0) * (1 - Pow5(1 - NoL)) + min(2 * a, 1)) * (1 - 0.5 * a * (NoL - 1)) * NoL;
    float Vd = (a2 / ((a2 + 0.09) * (1.31072 + 0.995584 * NoV))) * (1 - pow(1 - NoL, (1 - 0.3726732 * NoV * NoV) / (0.188566 + 0.38841 * NoV)));
    float Bp = Cosri < 0 ? 1.4 * NoV * NoL * Cosri : Cosri;
    float Lr = (21.0 / 20.0) * (1 - F0) * (Fr * Lm + Vd + Bp);
    return DiffuseColor / PI * Lr;
#else
	float a2_13 = a2 + 1.36053;
	float Fr = (1 - (0.542026*a2 + 0.303573*a) / a2_13) * (1 - pow(1 - NoV, 5 - 4 * a2) / a2_13) * ((-0.733996*a2*a + 1.50912*a2 - 1.16402*a) * pow(1 - NoV, 1 + rcp(39 * a2*a2 + 1)) + 1);
	float Lm = (max(1 - 2 * a, 0) * (1 - Pow5(1 - NoL)) + min(2 * a, 1)) * (1 - 0.5*a + 0.5*a * NoL);
	float Vd = (a2 / ((a2 + 0.09) * (1.31072 + 0.995584 * NoV))) * (1 - pow(1 - NoL, (1 - 0.3726732 * NoV * NoV) / (0.188566 + 0.38841 * NoV)));
	float Bp = Cosri < 0 ? 1.4 * NoV * Cosri : Cosri / max(NoL, 1e-8);
	float Lr = (21.0 / 20.0) * (1 - F0) * (Fr * Lm + Vd + Bp);
	return DiffuseColor / PI * Lr;
#endif
}

// [Blinn 1977, "Models of light reflection for computer synthesized pictures"]
float D_Blinn(float a2, float NoH)
{
    float n = 2 / a2 - 2;
    return (n + 2) / (2 * PI) * PhongShadingPow(NoH, n); // 1 mad, 1 exp, 1 mul, 1 log
}

// [Beckmann 1963, "The scattering of electromagnetic waves from rough surfaces"]
float D_Beckmann(float a2, float NoH)
{
    float NoH2 = NoH * NoH;
    return exp((NoH2 - 1) / (a2 * NoH2)) / (PI * a2 * NoH2 * NoH2);
}

// GGX / Trowbridge-Reitz
// [Walter et al. 2007, "Microfacet models for refraction through rough surfaces"]
float D_GGX(float a2, float NoH)
{
    float d = (NoH * a2 - NoH) * NoH + 1; // 2 mad
    return a2 / (PI * d * d); // 4 mul, 1 rcp
}

// Anisotropic GGX
// [Burley 2012, "Physically-Based Shading at Disney"]
float D_GGXaniso(float ax, float ay, float NoH, float3 H, float3 X, float3 Y)
{
    float XoH = dot(X, H);
    float YoH = dot(Y, H);
    float d = XoH * XoH / (ax * ax) + YoH * YoH / (ay * ay) + NoH * NoH;
    return 1 / (PI * ax * ay * d * d);
}

// [Neumann et al. 1999, "Compact metallic reflectance models"]
float Vis_Neumann(float NoV, float NoL)
{
    return 1 / (4 * max(NoL, NoV));
}

// [Kelemen 2001, "A microfacet based coupled specular-matte brdf model with importance sampling"]
float Vis_Kelemen(float VoH)
{
	// constant to prevent NaN
    return rcp(4 * VoH * VoH + 1e-5);
}

// Tuned to match behavior of Vis_Smith
// [Schlick 1994, "An Inexpensive BRDF Model for Physically-Based Rendering"]
float Vis_Schlick(float a2, float NoV, float NoL)
{
    float k = sqrt(a2) * 0.5;
    float Vis_SchlickV = NoV * (1 - k) + k;
    float Vis_SchlickL = NoL * (1 - k) + k;
    return 0.25 / (Vis_SchlickV * Vis_SchlickL);
}

// Smith term for GGX
// [Smith 1967, "Geometrical shadowing of a random rough surface"]
float Vis_Smith(float a2, float NoV, float NoL)
{
    float Vis_SmithV = NoV + sqrt(NoV * (NoV - NoV * a2) + a2);
    float Vis_SmithL = NoL + sqrt(NoL * (NoL - NoL * a2) + a2);
    return rcp(Vis_SmithV * Vis_SmithL);
}

// Appoximation of joint Smith term for GGX
// [Heitz 2014, "Understanding the Masking-Shadowing Function in Microfacet-Based BRDFs"]
float Vis_SmithJointApprox(float a2, float NoV, float NoL)
{
    float a = sqrt(a2);
    float Vis_SmithV = NoL * (NoV * (1 - a) + a);
    float Vis_SmithL = NoV * (NoL * (1 - a) + a);
    return 0.5 * rcp(Vis_SmithV + Vis_SmithL);
}

float3 F_None(float3 SpecularColor)
{
    return SpecularColor;
}

// [Schlick 1994, "An Inexpensive BRDF Model for Physically-Based Rendering"]
float3 F_Schlick(float3 SpecularColor, float VoH)
{
    float Fc = Pow5(1 - VoH);					// 1 sub, 3 mul
    //return Fc + (1 - Fc) * SpecularColor;		// 1 add, 3 mad

    // Anything less than 2% is physically impossible and is instead considered to be shadowing
    return saturate(50.0 * SpecularColor.g) * Fc + (1 - Fc) * SpecularColor;

}


//---------------
// EnvBRDF
//---------------
float3 EnvBRDFApprox(float3 SpecularColor, float Roughness, float NoV)
{
	// [ Lazarov 2013, "Getting More Physical in Call of Duty: Black Ops II" ]
	// Adaptation to fit our G term.
    const float4 c0 = { -1, -0.0275, -0.572, 0.022 };
    const float4 c1 = { 1, 0.0425, 1.04, -0.04 };
    float4 r = Roughness * c0 + c1;
    float a004 = min(r.x * r.x, exp2(-9.28 * NoV)) * r.x + r.y;
    float2 AB = float2(-1.04, 1.04) * a004 + r.zw;

	// Anything less than 2% is physically impossible and is instead considered to be shadowing
	// Note: this is needed for the 'specular' show flag to work, since it uses a SpecularColor of 0
    AB.y *= saturate(50.0 * SpecularColor.g);

    return SpecularColor * AB.x + AB.y;
}

float EnvBRDFApproxNonmetal(float Roughness, float NoV)
{
	// Same as EnvBRDFApprox( 0.04, Roughness, NoV )
    const float2 c0 = { -1, -0.0275 };
    const float2 c1 = { 1, 0.0425 };
    float2 r = Roughness * c0 + c1;
    return min(r.x * r.x, exp2(-9.28 * NoV)) * r.x + r.y;
}

struct BxDFContext
{
    float NoV;
    float NoL;
    float VoL;
    float NoH;
    float VoH;
};


float3 SpecularGGX(float Roughness, float3 SpecularColor, BxDFContext Context, float NoL)
{
    float a2 = Pow4(Roughness);
	
	// Generalized microfacet specular
    float D = D_GGX(a2, Context.NoH);
    float Vis = Vis_SmithJointApprox(a2, Context.NoV, NoL);
    float3 F = F_Schlick(SpecularColor, Context.VoH);

    return (D * Vis) * F;
}

float PhongApprox(float Roughness, float RoL)
{
    float a = Roughness * Roughness; // 1 mul
	//!! Ronin Hack?
    a = max(a, 0.008); // avoid underflow in FP16, next sqr should be bigger than 6.1e-5
    float a2 = a * a; // 1 mul
    float rcp_a2 = rcp(a2); // 1 rcp
	//float rcp_a2 = exp2( -6.88886882 * Roughness + 6.88886882 );

	// Spherical Gaussian approximation: pow( x, n ) ~= exp( (n + 0.775) * (x - 1) )
	// Phong: n = 0.5 / a2 - 0.5
	// 0.5 / ln(2), 0.275 / ln(2)
    float c = 0.72134752 * rcp_a2 + 0.39674113; // 1 mad
    float p = rcp_a2 * exp2(c * RoL - c); // 2 mad, 1 exp2, 1 mul
	// Total 7 instr
    return min(p, rcp_a2); // Avoid overflow/underflow on Mali GPUs
}

float CalcSpecular(float Roughness, float RoL, float NoH, float3 H, float3 N)
{
    return PhongApprox(Roughness, RoL);
}

#define REFLECTION_CAPTURE_ROUGHEST_MIP 1
#define REFLECTION_CAPTURE_ROUGHNESS_MIP_SCALE 1.2

/** 
 * Compute absolute mip for a reflection capture cubemap given a roughness.
 */
float ComputeReflectionCaptureMipFromRoughness(float Roughness, float CubemapMaxMip)
{
	// Heuristic that maps roughness to mip level
	// This is done in a way such that a certain mip level will always have the same roughness, regardless of how many mips are in the texture
	// Using more mips in the cubemap just allows sharper reflections to be supported
    float LevelFrom1x1 = REFLECTION_CAPTURE_ROUGHEST_MIP - REFLECTION_CAPTURE_ROUGHNESS_MIP_SCALE * log2(Roughness);
    return CubemapMaxMip - 1 - LevelFrom1x1;
}
