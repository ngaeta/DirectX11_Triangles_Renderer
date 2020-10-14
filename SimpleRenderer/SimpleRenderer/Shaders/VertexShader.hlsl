struct vertex_in
{
	float3 pos : POS; 
	float2 tex : TEX;
};

struct vertex_out
{
	float4 pos : SV_POSITION; 
	float2 tex : TEX;
};

cbuffer uniform_t
{
	matrix model;
};

vertex_out main(vertex_in input)
{
	vertex_out output;
	output.pos = mul(model, float4(input.pos, 1.0));
	output.tex = input.tex;
	return output;
}