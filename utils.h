#pragma once
#include "glm/glm.hpp"
#include <ostream>

inline std::ostream& operator<<(std::ostream& out, const glm::vec3& vec)
{
	return out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
}

inline float saturate(float a) { return glm::clamp(a, 0.f, 1.f); }
inline glm::vec3 saturate(const glm::vec3& a)
{
	return glm::vec3(saturate(a.x), saturate(a.y), saturate(a.z));
}