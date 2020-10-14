#pragma once

#include "Context.h"
#include <string>
#include <glm/vec3.hpp>
#include "IShaderResource.h"

class Texture : public IShaderResource
{
public:
	Texture() = default;
	Texture(const Context& context, const std::string imageFilePath);

	ID3D11ShaderResourceView* const* GetResourceView() const override { return textureView.GetAddressOf(); }

private:
	ComPtr<ID3D11Texture2D> texture;
	ComPtr<ID3D11ShaderResourceView> textureView;
	glm::ivec3 imageSize;
};

