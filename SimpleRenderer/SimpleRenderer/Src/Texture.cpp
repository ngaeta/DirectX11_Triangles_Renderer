#include "Texture.h"
#include "FileHelper.h"
#include <memory>

Texture::Texture(const Context& context, const std::string imageFilePath)
{
	std::unique_ptr<uint8_t[]> image_data = FileHelper::LoadImageFile(imageFilePath, imageSize);

	D3D11_TEXTURE2D_DESC texture_desc{};
	texture_desc.Width = imageSize.x;
	texture_desc.Height = imageSize.y;
	texture_desc.MipLevels = 1;  
	texture_desc.ArraySize = 1;
	texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	texture_desc.SampleDesc.Count = 1;
	texture_desc.SampleDesc.Quality = 0;
	texture_desc.Usage = D3D11_USAGE_DEFAULT;
	texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;  
	texture_desc.CPUAccessFlags = 0;
	texture_desc.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA texture_data{};
	texture_data.pSysMem = image_data.get();
	texture_data.SysMemPitch = imageSize.x * 4;
	context.GetDevice()->CreateTexture2D(&texture_desc, &texture_data, &texture);

	D3D11_SHADER_RESOURCE_VIEW_DESC texture_view_desc{};
	texture_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	texture_view_desc.Format = texture_desc.Format;
	texture_view_desc.Texture2D.MipLevels = 1;
	texture_view_desc.Texture2D.MostDetailedMip = 0;
	context.GetDevice()->CreateShaderResourceView(texture.Get(), &texture_view_desc, &textureView);
}
