#pragma once

#include "glm/vec3.hpp"
#include <glm\ext\matrix_float4x4_precision.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3 position, const glm::vec3 rotation, const float ratio);
	Camera(const Camera&) = delete;
	Camera(Camera&&) = delete;
	Camera& operator=(const Camera&) = delete;
	Camera& operator=(Camera&&) = delete;

	const glm::highp_mat4 GetModel() 
	{ 
		return glm::perspective(glm::radians(fov), ratio, zNear, zFar) * glm::lookAt(rotation, position, up);
	}

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 up { 0.f, 1.0f, 0.f };
	float fov = 90.f;
	float zNear = 0.1f;
	float zFar = 100.0f;
	const float ratio;
};

