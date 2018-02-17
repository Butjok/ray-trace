#include "camera.h"

float Camera::defaultFov = 90;

glm::vec3 Camera::ray(glm::vec2 uv) const
{
	uv *= 2;
	uv -= glm::vec2(1, 1);

	auto right = cross(forward, up);
	auto up = cross(right, forward);
	auto end = forward + uv.x*right + uv.y*up;
	return normalize(end);
}