#pragma once

#include <vector>
#include <memory>

#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL 
#include "glm/gtx/intersect.hpp"

#include "sphere.h"

struct Light;

struct Hit
{
	const Sphere* sphere;
	float distance;
	glm::vec3 point;
	glm::vec3 normal;
};

struct Scene
{
	std::vector<Sphere> spheres;
	std::vector<std::shared_ptr<Light>> lights;

	bool intersect(const glm::vec3& ray_start, const glm::vec3& ray_direction, Hit& hit) const;
	bool test(const glm::vec3& ray_start, const glm::vec3& ray_direction, const Sphere* ignoredSphere = nullptr) const;
};
