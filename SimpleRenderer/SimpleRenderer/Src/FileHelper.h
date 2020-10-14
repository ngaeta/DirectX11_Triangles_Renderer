#pragma once

#include <vector>
#include <string>
#include <glm/vec3.hpp>
#include <memory>

class FileHelper
{
	FileHelper() = delete;
	FileHelper(const FileHelper&) = delete;
	FileHelper& operator=(const FileHelper&) = delete;
	FileHelper& operator=(FileHelper&&) = delete;
	FileHelper(FileHelper&&) = delete;

public:
	static const std::vector<uint8_t> LoadFile(const std::string& path);
	static std::unique_ptr<uint8_t[]> LoadImageFile(const std::string filename, glm::ivec3& imageSize);
};

