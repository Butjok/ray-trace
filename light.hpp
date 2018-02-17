#pragma once

#include "glm/glm.hpp"
#include "sphere.h"
#include "scene.h"

struct Light
{
	glm::vec3 color;

	explicit Light(glm::vec3 color = glm::vec3(0,0,0))
		:color(color)
	{}
	virtual ~Light() = default;
	virtual float attenuation(const glm::vec3& position, const Sphere* ignoredSphere, const Scene& scene) const = 0;
	virtual glm::vec3 to_light(const glm::vec3& position, const glm::vec3& normal) const = 0;
};

struct DirectionalLight : Light
{
	glm::vec3 forward;

	explicit DirectionalLight(glm::vec3 color = glm::vec3(0, 0, 0), glm::vec3 forward = glm::vec3(1, 0, 0))
		:Light(color), forward(normalize(forward))
	{}

	float attenuation(const glm::vec3& position, const Sphere* ignoredSphere, const Scene& scene) const override
	{
		return scene.test(position, -forward, ignoredSphere) ? 0 : 1.0f;
	}
	glm::vec3 to_light(const glm::vec3& position, const glm::vec3& normal) const override
	{
		return -forward;
	}
};

struct AmbientLight : Light
{
	explicit AmbientLight(glm::vec3 color = glm::vec3(0, 0, 0))
		:Light(color)
	{}

	float attenuation(const glm::vec3& position, const Sphere* ignoredSphere, const Scene& scene) const override
	{
		return 1;
	}
	glm::vec3 to_light(const glm::vec3& position, const glm::vec3& normal) const override
	{
		return normal;
	}
};