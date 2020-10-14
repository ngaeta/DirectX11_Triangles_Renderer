#pragma once

#include <d3d11.h>
#include <stdint.h>
#include "Context.h"
#include <wrl.h>
using namespace Microsoft::WRL;

class Buffer
{
public:
	template<typename T>
	Buffer(const Context& context, const D3D11_BIND_FLAG type, const T* const data, const uint32_t size_ = sizeof(T)) 
		: stride{ sizeof(T) }, size {size_}
	{
		D3D11_BUFFER_DESC vbo_desc{};
		vbo_desc.ByteWidth = size_;
		vbo_desc.Usage = D3D11_USAGE_DEFAULT;
		vbo_desc.BindFlags = (UINT)type;
		vbo_desc.StructureByteStride = sizeof(T);
		D3D11_SUBRESOURCE_DATA vbo_data{};
		vbo_data.pSysMem = data;
		context.GetDevice()->CreateBuffer(&vbo_desc, &vbo_data, &this->data);
	}

	Buffer(Buffer&& other) noexcept
	{
		data = std::move(other.data);
		stride = std::move(other.stride);
		other.data = nullptr;
	}

	Buffer& operator=(Buffer&& other) noexcept
	{
		data = std::move(other.data);
		stride = std::move(other.stride);
		return *this;
	}

	template<typename T>
	void UpdateData(const Context& context, const T* newData, const uint32_t size_ = sizeof(T)) const
	{
		context.GetDeviceContext()->UpdateSubresource(data.Get(), 0, nullptr, newData, size_, 0);
	}

	ID3D11Buffer* GetData() const { return data.Get(); }
	ID3D11Buffer* const* GetDataAddress() { return data.GetAddressOf(); }
	inline const uint32_t& GetStride() const { return stride; }
	const uint32_t GetSize() const { return size; }

	uint32_t Offset = 0;

private:
	ComPtr<ID3D11Buffer> data;
	uint32_t stride;
	uint32_t size;
};

