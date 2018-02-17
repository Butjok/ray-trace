#pragma once

#include "glm/glm.hpp"
#include "utils.h"

inline glm::vec3 ACESFilm(const glm::vec3& x)
{
	float a = 2.51f;
	float b = 0.03f;
	float c = 2.43f;
	float d = 0.59f;
	float e = 0.14f;
	return saturate((x*(a*x + b)) / (x*(c*x + d) + e));
}