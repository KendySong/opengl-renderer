#if DEBUG
	#include <iostream>
#endif

#include "Mesh.hpp"

Mesh::Mesh(MeshType type, float size, Shader* shader) : m_type(type), shader(shader)
{
	std::uint32_t indices[] {
		0, 1, 3,
		1, 2, 3
	};

	this->material.albedo = glm::vec3(1);
	switch (type)
	{
	case MeshType::Triangle :
		m_vertices = {
			{ {  0,     size, 0 }, { 0, 0, 0 }, { 0, 0 } },
			{ { -size, -size, 0 }, { 0, 0, 0 }, { 0, 0 } },
			{ {  size, -size, 0 }, { 0, 0, 0 }, { 0, 0 } }
		};
		
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);
		break;

	case MeshType::Rect :
		m_vertices = {
			{ { size,   size, 0 }, { 0, 0, 0 }, { 1, 1 } },
			{ { size,  -size, 0 }, { 0, 0, 0 }, { 1, 0 } },
			{ { -size, -size, 0 }, { 0, 0, 0 }, { 0, 0 } },
			{ { -size,  size, 0 }, { 0, 0, 0 }, { 0, 1 } }
		};
	
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &m_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
		break;

	default :
#if DEBUG
		std::cout << "[ERROR] mesh type unkndown : " << static_cast<int>(type) << '\n';
#endif
		break;
	}

	Vertex::config();
}

void Mesh::draw()
{
	glm::mat4x4 world(1);
	world = glm::translate(world, this->transform.position);
	world = glm::rotate(world, this->transform.rotation.x, glm::vec3(1, 0, 0));
	world = glm::rotate(world, this->transform.rotation.y, glm::vec3(0, 1, 0));
	world = glm::rotate(world, this->transform.rotation.z, glm::vec3(0, 0, 1));
	world = glm::scale(world, this->transform.scale);

	this->shader->bind();
	this->shader->uniformMat4("u_world", world);
	this->shader->uniformVec3("u_color", this->material.albedo);
	glBindVertexArray(m_vao);
	this->texture.bind();

	switch (m_type)
	{
	case MeshType::Triangle :
		glDrawArrays(GL_TRIANGLES, 0, 3);
		break;

	case MeshType::Rect :
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		break;
	}
}

void Mesh::remove()
{
	glDeleteBuffers(1, &m_ebo);
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}