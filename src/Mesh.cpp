#if DEBUG
	#include <iostream>
#endif

#include "Mesh.hpp"

Mesh::Mesh(MeshType type, float size) : m_type(type)
{
	std::uint32_t vbo = 0;

	switch (type)
	{
	case MeshType::Triangle :
		m_vertices = {
			{ {  0,     size, 0 }, { 0, 1, 0 }, { 0, 0 } },
			{ { -size, -size, 0 }, { 1, 0, 0 }, { 0, 0 } },
			{ {  size, -size, 0 }, { 0, 0, 1 }, { 0, 0 } }
		};
		
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
		glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(2 * sizeof(glm::vec3)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		break;

	case MeshType::Rect :
		m_vertices = {
			{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0 } },
			{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0 } },
			{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0 } },
			{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0 } }
		};
		break;

	default :
#if DEBUG
		std::cout << "[ERROR] mesh type unkndown : " << static_cast<int>(type) << '\n';
#endif
		exit(0);
		break;
	}
}

void Mesh::draw()
{
	switch (m_type)
	{
	case MeshType::Triangle:
		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		break;

	case MeshType::Rect:

		break;
	}
}