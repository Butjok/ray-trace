#pragma once

#include "glm/glm.hpp"

struct Sphere
{
	glm::vec3 position;
	float radius;
	glm::vec3 color;

	Sphere(glm::vec3 position, float radius, glm::vec3 color = glm::vec3())
		:position(position), radius(radius), color(color)
	{}
};
