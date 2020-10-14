#define STB_IMAGE_IMPLEMENTATION

#include "FileHelper.h"
#include "../Libs/stb/stb_image.h"
#include <fstream>
#include <iostream>

const std::vector<uint8_t> FileHelper::LoadFile(const std::string& path)
{
	std::ifstream ifs(path, std::ios::binary | std::ios::ate);
	if (ifs.is_open())
	{
		size_t size = ifs.tellg();
		std::vector<uint8_t> buffer(size);
		ifs.seekg(std::ios::beg);
		ifs.read(reinterpret_cast<char*>(buffer.data()), size);
		return buffer;
	}

	return {};
}

std::unique_ptr<uint8_t[]> FileHelper::LoadImageFile(const std::string filename, glm::ivec3& imageSize)
{
	std::unique_ptr<uint8_t[]> imageData{ stbi_load(filename.c_str(), &imageSize.x, &imageSize.y, &imageSize.z, 4) };
	return std::move(imageData);
}
