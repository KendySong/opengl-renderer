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
	Mesh(MeshType type, float size, Shader* shader);
	void draw();
	void remove();

	Shader* shader;
	Transform transform;
	Material material;
	RenderType renderType;
	std::shared_ptr<Texture> texture;

private :
	MeshType m_type;
	std::vector<Vertex> m_vertices;
	std::uint32_t m_vao;
	std::uint32_t m_vbo;
	std::uint32_t m_ebo;
};