#include "Material.hpp"

Material::Material()
{
	albedo = glm::vec3(0, 0, 0);
}

Material::Material(const glm::vec3& albedo)
{
	this->albedo = albedo;
}