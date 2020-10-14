#include <vector>
#include <string>
#include <d3d11.h>
#include <dxgi.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Src/Window.h"
#include "Src/Context.h"
#include "Src/Context.h"
#include "Src/Mesh.h"
#include "Src/Buffer.h"
#include "Src/Shader.h"
#include "Src/VertexShader.h"
#include "Src/PixelShader.h"
#include "Src/Texture.h"

#include <wrl.h>
#include "Src/Camera.h"
#include <iostream>
using namespace Microsoft::WRL;

int main()
{
	Window window(800, 600);
	window.Show();

	Context context(window);

	std::vector<Vertex> triangle_data
	{
		Vertex({ -0.5f, -0.5f,  0.0f }, { 0.0f, 0.0f }),
		Vertex({ -0.5f,  0.5f,  0.0f }, { 0.0f, 1.0f }),
		Vertex({  0.5f,  0.5f,  0.0f }, { 1.0f, 1.0f }),
		Vertex({  0.5f, -0.5f,  0.0f }, { 1.0f, 0.0f }),
	};
	std::vector<uint32_t> triangle_indices{ 0, 1, 2, 0, 2, 3 };
	Mesh mesh(context, triangle_data, triangle_indices);
	mesh.SetTexture(context, "Images/dx11_green.jpg");
	mesh.SetPosition(1.0f, 0, 0);
	mesh.SetRotation(0, 0, 180.0f);
	mesh.SetScale(1.5f);
	Mesh mesh2(context, triangle_data, triangle_indices);
	mesh2.SetTexture(context, "Images/dx11_red.png");
	mesh2.SetPosition(-1.0f, 0, 0);
	mesh2.SetRotation(0, 0, 180.0f);
	mesh2.SetScale(1.5f);

	std::vector<Mesh*> meshes{ &mesh, &mesh2 };

	VertexUniform vertex_uniform_data;
	Buffer vertex_uniform_buffer(context, D3D11_BIND_CONSTANT_BUFFER, &vertex_uniform_data);

	PixelUniform pixel_uniform_data;
	pixel_uniform_data.color = glm::vec4{ 1, 1, 1, 1 };
	Buffer pixel_uniform_buffer(context, D3D11_BIND_CONSTANT_BUFFER, &pixel_uniform_data);

	VertexShader vertexShader(context, "VertexShader.cso");
	vertexShader.SetConstantBuffer(context, vertex_uniform_buffer);
	PixelShader pixelShader(context, "PixelShader.cso");
	pixelShader.SetConstantBuffer(context, pixel_uniform_buffer);

	Camera camera{ glm::vec3(0.f), glm::vec3(0.f, 0.f, 3.f), window.GetAspectRatio() };

	const std::array<float, 4> color{ 0, 0, 1, 1 };
	window.OnUpdate = [&]()
	{
		context.ClearRenderTargetView(color);
		context.OMSetDefaultRenderTargets();

		context.SetVertexShader(vertexShader);
		context.SetPixelShader(pixelShader);

		for (int i = 0; i < meshes.size(); i++)
		{
			pixelShader.SetShaderResources(context, meshes[i]->GetTexture());
			vertex_uniform_data.mvp = camera.GetModel() * meshes[i]->GetModel();
			vertex_uniform_buffer.UpdateData(context, &vertex_uniform_data);
			context.RenderMesh(*meshes[i]);
		}

		context.Present();
	};

	window.Run(context);

	return EXIT_SUCCESS;
}

