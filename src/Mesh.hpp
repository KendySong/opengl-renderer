#pragma once
#include <vector>

#include <glad/glad.h>

#include "Transform.hpp"
#include "MeshType.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"

class Mesh
{
public :
	Mesh() = default;
	Mesh(MeshType type, float size, Shader* shader);
	void draw();

	glm::vec3 color;
	Transform transform;
	Shader* shader;

private :
	void configInput();

	MeshType m_type;
	std::vector<Vertex> m_vertices;
	std::uint32_t m_vao;
	std::uint32_t m_ebo;
};