#pragma once

#include "Shader.h"

class VertexShader : public Shader<ID3D11VertexShader>
{
public:
	VertexShader(const Context& context, const std::string path);

	void SetConstantBuffer(const Context& context, Buffer& buffer) override;
	void SetShaderResources(const Context& context, const IShaderResource& resource) const override;
	void CreateShader(const Context& context) override;
};

