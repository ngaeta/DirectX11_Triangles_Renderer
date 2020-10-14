#include "Mesh.h"

Mesh::Mesh(const Context& context, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indexes) :
	vertexBuffer{context, D3D11_BIND_VERTEX_BUFFER, vertices.data(), vertices.size() * sizeof(Vertex)},
	indexBuffer{context, D3D11_BIND_INDEX_BUFFER, indexes.data(), indexes.size() * sizeof(uint32_t)},
	position{ glm::translate(glm::vec3(0)) }, 
	rotation{ glm::eulerAngleXYZ(glm::radians(0.f), glm::radians(0.f), glm::radians(0.f)) },
	scale{ glm::scale(glm::vec3(1)) }
{ 
}

void Mesh::SetTexture(const Context& context, std::string path)
{
	texture = Texture(context, path);
}

void Mesh::SetPosition(const float x, const float y, const float z)
{
	position = glm::translate(glm::vec3(x, y, z));
}

void Mesh::SetRotation(const float x, const float y, const float z)
{
	rotation = glm::eulerAngleXYZ(glm::radians(x), glm::radians(y), glm::radians(z));
}

void Mesh::SetScale(const float x, const float y, const float z)
{
	scale = glm::scale(glm::vec3(x, y, z));
}

void Mesh::SetScale(const float value)
{
	scale = glm::scale(glm::vec3(value));
}

