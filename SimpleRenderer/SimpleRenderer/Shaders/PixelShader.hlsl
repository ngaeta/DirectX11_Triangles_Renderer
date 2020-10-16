struct pixel_in
{
	float4 pos : SV_POSITION;
	float2 tex : TEX;
};

struct pixel_out
{
	float4 col : SV_TARGET;
};

cbuffer uniform_t {
	float4 color;
};

Texture2D Texture;
sampler   Sampler;  

pixel_out main(pixel_in input)
{
	pixel_out output;
	output.col = color * Texture.Sample(Sampler, float2(1 - input.tex.r, input.tex.g));
	//output.col = color * Texture.Sample(Sampler, input.tex);
	return output;
}
