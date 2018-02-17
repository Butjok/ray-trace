#pragma once

#include "glm/glm.hpp"

extern glm::vec3 forward;
extern glm::vec3 up;

struct Camera
{
	glm::vec3 position;
	glm::vec3 forward;
	float fov;

	static float defaultFov;

	explicit Camera(
		glm::vec3 position = glm::vec3(),
		glm::vec3 forward = ::forward,
		float fov = defaultFov)
		:position(position), forward(normalize(forward)), fov(fov)
	{}

	glm::vec3 ray(glm::vec2 uv) const;
};