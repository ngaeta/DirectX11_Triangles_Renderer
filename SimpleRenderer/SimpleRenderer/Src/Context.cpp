#include "Context.h"
#include "Buffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "Mesh.h"

Context::Context(const Window& window)
{
	DXGI_SWAP_CHAIN_DESC swapchain_desc{};
	swapchain_desc.BufferDesc.Width = window.Width();
	swapchain_desc.BufferDesc.Height = window.Height();
	swapchain_desc.BufferDesc.RefreshRate = { 0, 1 };
	swapchain_desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapchain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapchain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapchain_desc.SampleDesc.Count = 1;
	swapchain_desc.SampleDesc.Quality = 0;
	swapchain_desc.BufferCount = 2;
	swapchain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchain_desc.OutputWindow = window.GetHandler();
	swapchain_desc.Windowed = true;
	swapchain_desc.Flags = 0;
	swapchain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	D3D_FEATURE_LEVEL feature_level;
	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG |
		D3D11_CREATE_DEVICE_SINGLETHREADED,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapchain_desc,
		&swapchain,
		&device,
		&feature_level,
		&context
	);

	swapchain->GetBuffer(0, IID_PPV_ARGS(&swapchain_buffer));
	device->CreateRenderTargetView(swapchain_buffer.Get(), nullptr, &rtt);
}

void Context::ClearRenderTargetView(const std::array<float, 4>& color) const
{
	context->ClearRenderTargetView(rtt.Get(), color.data());
}

void Context::SetPixelShader(PixelShader& pixelShader) const
{
	context->PSSetShader(pixelShader.GetShaderPtr(), nullptr, 0);
	context->PSSetSamplers(0, 1, pixelShader.GetSamplerAddress());
}

void Context::RenderMesh(Mesh& mesh) const
{
	Buffer& vertexBuffer = mesh.GetVBuffer();
	Buffer& indexesBuffer = mesh.GetIBuffer();

	context->IASetVertexBuffers(0, 1, vertexBuffer.GetDataAddress(), &vertexBuffer.GetStride(), &vertexBuffer.Offset);
	context->IASetIndexBuffer(indexesBuffer.GetData(), DXGI_FORMAT_R32_UINT, indexesBuffer.Offset);
	context->DrawIndexed(mesh.GetVerticesIndexesSize(), 0, 0);
}

void Context::Present() const
{
	swapchain->Present(1, 0);
}

void Context::SetVertexShader(VertexShader& vertexShader) const
{
	context->VSSetShader(vertexShader.GetShaderPtr(), nullptr, 0);
}

void Context::OMSetDefaultRenderTargets() const
{
	std::array<ID3D11RenderTargetView*, 1> render_targets{ rtt.Get() };
	context->OMSetRenderTargets((uint32_t)render_targets.size(), render_targets.data(), nullptr);
}

