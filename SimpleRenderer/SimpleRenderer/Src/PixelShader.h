#pragma once

#include "Shader.h"
#include "Buffer.h"


class PixelShader : public Shader<ID3D11PixelShader>
{
public:
	PixelShader(const Context& context, const std::string path, D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_TEXTURE_ADDRESS_MODE addressMode = D3D11_TEXTURE_ADDRESS_WRAP);

	void CreateShader(const Context& context) override;		
	void SetConstantBuffer(const Context& context, Buffer& buffer) override;
	void SetShaderResources(const Context& context, const IShaderResource& resource) const override;

	const ComPtr<ID3D11SamplerState> GetSampler() const { return sampler; }

private:
	ComPtr<ID3D11SamplerState> sampler;
};

