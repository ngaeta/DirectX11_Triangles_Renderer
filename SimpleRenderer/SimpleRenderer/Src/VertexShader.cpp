#include "VertexShader.h"
#include "MeshHelper.h"
#include "Buffer.h"

VertexShader::VertexShader(const Context& context, const std::string path) : Shader(context, path)
{
	CreateShader(context);

	std::vector<D3D11_INPUT_ELEMENT_DESC> input_layout_desc = Vertex::GetLayout();
	context.GetDevice()->CreateInputLayout(input_layout_desc.data(), (uint32_t)input_layout_desc.size(),
		data.data(), (uint32_t) data.size(), &inputLayout);

	context.GetDeviceContext()->IASetInputLayout(inputLayout.Get());
}

void VertexShader::SetConstantBuffer(const Context& context, Buffer& buffer)
{
	context.GetDeviceContext()->VSSetConstantBuffers(0, 1, buffer.GetDataAddress());
}

void VertexShader::SetShaderResources(const Context& context, const IShaderResource& resource) const
{
	context.GetDeviceContext()->VSSetShaderResources(0, 1, resource.GetResourceView());
}

void VertexShader::CreateShader(const Context& context)
{
	context.GetDevice()->CreateVertexShader(data.data(), data.size(), nullptr, &shaderPtr);
}
