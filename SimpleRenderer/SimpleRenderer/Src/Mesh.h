#pragma once

#include <vector>
#include "MeshHelper.h"
#include <string>
#include "Texture.h"
#include "Buffer.h"

class Mesh 
{
public:
	Mesh(const Context& context, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indexes);
	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;
	Mesh(Mesh&&) = delete;
	Mesh&& operator=(Mesh&&) = delete;

	void SetTexture(const Context& context, std::string path);
	void SetPosition(const float x, const float y, const float z);
	void SetRotation(const float x, const float y, const float z);
	void SetScale(const float x, const float y, const float z);
	void SetScale(const float value);

	Buffer& GetVBuffer() { return vertexBuffer; }
	Buffer& GetIBuffer() { return indexBuffer; }
	const uint32_t GetVerticesIndexesSize() const { return indexBuffer.GetSize(); }
	const Texture& GetTexture() const { return texture; }
	const glm::highp_mat4 GetModel() const { return position * rotation * scale; }

private:
	Buffer vertexBuffer;
	Buffer indexBuffer;
	glm::highp_mat4 position;
	glm::highp_mat4 rotation;
	glm::highp_mat4 scale;
	Texture texture;
};

