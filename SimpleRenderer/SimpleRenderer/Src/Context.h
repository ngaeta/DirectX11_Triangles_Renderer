#pragma once

#include <array>
#include <d3d11.h>
#include "Window.h"
#include <wrl.h>
using namespace Microsoft::WRL;

class Buffer;
class PixelShader;
class VertexShader;
class Mesh;

class Context
{

public:
	Context(const Window&);
	Context(const Context&) = delete;
	Context& operator=(const Context&) = delete;
	Context(Context&&) = delete;
	Context& operator=(Context&&) = delete;

	void OMSetDefaultRenderTargets() const;
	void ClearRenderTargetView(const std::array<float, 4>& color) const;
	void SetVertexShader(VertexShader& vertexShader) const;
	void SetPixelShader(PixelShader& pixelShader) const;
	void RenderMesh(Mesh& mesh) const;
	void Present() const;

	inline ID3D11Device* GetDevice() const { return device.Get(); }
	inline ID3D11DeviceContext* GetDeviceContext() const { return context.Get(); }

private:
	ComPtr<ID3D11Device> device; 
	ComPtr<ID3D11DeviceContext> context;  
	ComPtr<IDXGISwapChain> swapchain; 
	ComPtr<ID3D11Texture2D> swapchain_buffer;  
	ComPtr<ID3D11RenderTargetView> rtt;  
};

