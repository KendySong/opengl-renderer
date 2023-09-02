#pragma once
#include <glm/glm.hpp>

struct Transform
{
	Transform();

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};