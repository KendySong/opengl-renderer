#pragma once
#include <glm/glm.hpp>

class Material
{
public :
	Material();
	Material(const glm::vec3& albedo);

	glm::vec3 albedo;
};