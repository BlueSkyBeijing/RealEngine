//Diffuse Light
//Lambert

float3 Lambert(float3 normal, float3 lightDir, float3 lightColor)
{
	float NdotL = max(0.0, dot(normal, lightDir));
	return lightColor * NdotL;
}

//Half-Lambert

float3 HalfLambert(float3 normal, float3 lightDir, float3 lightColor)
{
	float NdotL = max(0.0, dot(normal, lightDir));
	float HalfLambertDiffuse = pow(NdotL * 0.5 + 0.5, 2.0);
	return lightColor * HalfLambertDiffuse;
}


// Specular
// Phong

float3 Phong(float3 normal, float3 lightDir, float3 lightColor, float3 specularColor, float specPower)
{
	float NdotL = max(0, dot(normal, lightDir));
	 
	float3 lightReflectDirection = reflect(-lightDir, normal);
	float RdotV = max(0, dot(lightReflectDirection, viewDir));
	float spec = pow(RdotV, specPower/4) * specularColor;	 
	return lightColor.rgb * NdotL) + (lightColor.rgb * specularColor.rgb * spec);
}

// Blinn-Phong

float3 BlinnPhong(float3 normal, float3 lightDir, float3 lightColor, float3 specularColor, float specPower)
{
	float NdotL = max(0, dot(normal, lightDir));
	 
	float3 halfVector = normalize(lightDir + viewDir);
	float NdotH = max(0, dot(normal, halfVector));
	float spec = pow(NdotH, specPower) * specularColor;
	 
	return lightColor.rgb * NdotL) + (lightColor.rgb * specularColor.rgb * spec);
}
