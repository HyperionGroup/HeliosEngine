Vert2Pix VertexStageMain(App2Vert in)
{
	Vert2Frag lOutput = (Vert2Frag)0;
	lOutput.position = float4( in.position, 1.0 );
	lOutput.uv = in.uv;
	return lOutput;
}

float4 PixelStageMain(Vert2Pix in) : SV_Target
{
	return T0Texture.Sample(S0Sampler, in.uv);
}