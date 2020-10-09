
const static float PI = 3.1415926535897932f;

// Clamp the base, so it's never <= 0.0f (INF/NaN).
float ClampedPow(float X, float Y)
{
    return pow(max(abs(X), 0.000001f), Y);
}

float PhongShadingPow(float X, float Y)
{
    return ClampedPow(X, Y);
}

float Pow4(float x)
{
    float xx = x * x;
    return xx * xx;
}

float Pow5(float x)
{
    float xx = x * x;
    return xx * xx * x;
}

float2 Pow5(float2 x)
{
    float2 xx = x * x;
    return xx * xx * x;
}

float Pow5(float3 x)
{
    float3 xx = x * x;
    return xx * xx * x;
}

float Pow5(float4 x)
{
    float4 xx = x * x;
    return xx * xx * x;
}

float4 RGBMEncode(float3 Color)
{
    Color *= 1.0 / 64.0;
	
    float4 rgbm;
    rgbm.a = saturate(max(max(Color.r, Color.g), max(Color.b, 1e-6)));
    rgbm.a = ceil(rgbm.a * 255.0) / 255.0;
    rgbm.rgb = Color / rgbm.a;
    return rgbm;
}

float4 RGBMEncodeFast(float3 Color)
{
	// 0/0 result written to fixed point buffer goes to zero
    float4 rgbm;
    rgbm.a = dot(Color, 255.0 / 64.0);
    rgbm.a = ceil(rgbm.a);
    rgbm.rgb = Color / rgbm.a;
    rgbm *= float4(255.0 / 64.0, 255.0 / 64.0, 255.0 / 64.0, 1.0 / 255.0);
    return rgbm;
}

float3 RGBMDecode(float4 rgbm, float MaxValue)
{
    return rgbm.rgb * (rgbm.a * MaxValue);
}

float3 RGBMDecode(float4 rgbm)
{
    return rgbm.rgb * (rgbm.a * 64.0f);
}
