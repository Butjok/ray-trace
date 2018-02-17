#pragma once
#include "glm/glm.hpp"

inline float lambert(const glm::vec3& normal, const glm::vec3& to_light)
{
	return glm::max(0.f, dot(normal, to_light));
}