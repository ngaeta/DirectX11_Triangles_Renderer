#pragma once

#include "Context.h"
#include <d3d11.h>
#include <string>
#include <vector>
#include "FileHelper.h"
#include "IShaderResource.h"
#include <wrl.h>
using namespace Microsoft::WRL;

class Buffer;

template<typename T>
class Shader
{
public:
	Shader(const Context& context, const std::string path)
	{
		data = FileHelper::LoadFile(path);
	}
	virtual ~Shader() = default;

	T* GetShaderPtr() { return shaderPtr.Get(); }

	virtual void SetShaderResources(const Context& context, const IShaderResource& resource) const = 0;
	virtual void SetConstantBuffer(const Context& context, Buffer& buffer) = 0;
	virtual void CreateShader(const Context& context) = 0;

protected:
	ComPtr<T> shaderPtr;
	ComPtr<ID3D11InputLayout> inputLayout;
	std::vector<uint8_t> data;
};
