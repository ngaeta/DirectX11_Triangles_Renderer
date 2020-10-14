#pragma once

#include <glm\ext\vector_float2.hpp>
#include <glm\ext\vector_float3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_major_storage.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <d3d11.h>

struct Vertex
{
	glm::vec3 pos;
	glm::vec2 tex;
	Vertex() = default;
	Vertex(glm::vec3 pos, glm::vec2 tex) : pos(pos), tex(tex) { }

	static std::vector<D3D11_INPUT_ELEMENT_DESC> GetLayout()
	{
		return {
			D3D11_INPUT_ELEMENT_DESC{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			D3D11_INPUT_ELEMENT_DESC{ "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
	}
};

struct PixelUniform
{
	glm::vec4 color;
	PixelUniform() : color(1, 0, 0, 1) { }
};

struct VertexUniform
{
	glm::mat4 mvp;  
	VertexUniform() : mvp(glm::identity<glm::mat4>()) { }
};
