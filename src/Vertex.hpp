#pragma once
#include <glm/glm.hpp>

struct Vertex
{
	static void config();

	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 uv;
};