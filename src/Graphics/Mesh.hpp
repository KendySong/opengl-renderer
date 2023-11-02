#pragma once
#include <vector>
#include <memory>

#include <glad/glad.h>

#include "RenderType.hpp"
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
	Mesh(MeshType type, float size, Shader* shader, glm::vec3 a = glm::vec3(), glm::vec3 b = glm::vec3());
	void draw();
	void remove();

public :
	Shader* shader;
	Transform transform;
	Material material;
	RenderType renderType;
	std::shared_ptr<Texture> texture;
	MeshType type;

private :
	std::vector<Vertex> m_vertices;
	std::uint32_t m_vao;
	std::uint32_t m_vbo;
	std::uint32_t m_ebo;
};