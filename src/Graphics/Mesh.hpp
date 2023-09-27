#pragma once
#include <vector>

#include <glad/glad.h>

#include "Transform.hpp"
#include "MeshType.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Texture.hpp"

class Mesh
{
public :
	Mesh() = default;
	Mesh(MeshType type, float size, Shader* shader);
	void draw();
	void remove();

	Texture texture;
	Material material;
	Transform transform;
	Shader* shader;

private :
	MeshType m_type;
	std::vector<Vertex> m_vertices;
	std::uint32_t m_vao;
	std::uint32_t m_vbo;
	std::uint32_t m_ebo;
};