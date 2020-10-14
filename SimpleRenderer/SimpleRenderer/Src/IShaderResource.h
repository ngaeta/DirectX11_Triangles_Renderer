#pragma once

#include <d3d11.h>

class IShaderResource
{
public:
	virtual ID3D11ShaderResourceView* const* GetResourceView() const = 0;
};

