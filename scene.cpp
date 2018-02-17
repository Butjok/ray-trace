#include "scene.h"

bool Scene::intersect(const glm::vec3& ray_start, const glm::vec3& ray_direction, Hit& hit) const
{
	hit.sphere = nullptr;
	auto min_distance = FLT_MAX;

	for (const auto& sphere : spheres)
	{
		float distance;
		if (intersectRaySphere(ray_start, ray_direction, sphere.position, sphere.radius * sphere.radius, distance) &&
			distance < min_distance)
		{
			min_distance = distance;
			hit.sphere = &sphere;
		}
	}

	if (hit.sphere)
	{
		hit.point = ray_start + ray_direction * min_distance;
		hit.normal = normalize(hit.point - hit.sphere->position);
	}

	return hit.sphere != nullptr;
}

bool Scene::test(const glm::vec3& ray_start, const glm::vec3& ray_direction, const Sphere* ignoredSphere /*= nullptr*/) const
{
	for (const auto& sphere : spheres)
	{
		float distance;
		if (&sphere != ignoredSphere && intersectRaySphere(ray_start, ray_direction, sphere.position, sphere.radius*sphere.radius, distance))
		{
			return true;
		}
	}
	return false;
}

