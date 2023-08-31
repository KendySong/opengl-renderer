#pragma once
#include <vector>

#include <glad/glad.h>

#include "MeshType.hpp"
#include "Vertex.hpp"

class Mesh
{
public :
	Mesh() = default;
	Mesh(MeshType type, float size);

	void draw();

private :
	MeshType m_type;
	std::vector<Vertex> m_vertices;
	std::uint32_t m_vao;
	std::uint32_t m_ebo;
};