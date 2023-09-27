#include <glad/glad.h>

#include "Vertex.hpp"

void Vertex::config()
{
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(2 * sizeof(glm::vec3)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}