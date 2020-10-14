#include "PixelShader.h"

PixelShader::PixelShader(const Context& context, const std::string path, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE addressMode)
	: Shader(context, path)
{
	CreateShader(context);

	D3D11_SAMPLER_DESC sampler_desc{};
	sampler_desc.Filter = filter;
	sampler_desc.AddressU = addressMode;
	sampler_desc.AddressV = addressMode;
	sampler_desc.AddressW = addressMode;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	context.GetDevice()->CreateSamplerState(&sampler_desc, &sampler);
}

void PixelShader::CreateShader(const Context& context)
{
	context.GetDevice()->CreatePixelShader(data.data(), data.size(), nullptr, &shaderPtr);
}

void PixelShader::SetConstantBuffer(const Context& context, Buffer& buffer)
{
	context.GetDeviceContext()->PSSetConstantBuffers(0, 1, buffer.GetDataAddress());
}

void PixelShader::SetShaderResources(const Context& context, const IShaderResource& resource) const
{
	context.GetDeviceContext()->PSSetShaderResources(0, 1, resource.GetResourceView());
}

