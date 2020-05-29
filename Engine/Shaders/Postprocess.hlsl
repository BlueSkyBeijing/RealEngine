
void DrawRectangle(float4 PosScaleBias, float2 InvTargetSize, float4 InPosition, out float4 OutPosition)
{
	OutPosition = InPosition;
	OutPosition.xy = -1.0f + 2.0f * (PosScaleBias.zw + (InPosition.xy * PosScaleBias.xy)) * InvTargetSize.xy;
	OutPosition.xy *= float2( 1, -1 );
}
