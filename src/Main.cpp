#include <cmath>
#include <array>
#include <vector>
#include <string>
#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Mesh.hpp"

const std::uint32_t width = 1280;
const std::uint32_t height = 720;

int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(width, height, "Triangle", NULL, NULL);
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));
	glViewport(0, 0, width, height);
	glClearColor(0, 0, 0, 0);

#if DEBUG
	Shader shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
	shader.bind();
#else
	Shader shader("vertex.glsl", "fragment.glsl");
	shader.bind();
#endif

	Mesh triangle(MeshType::Triangle, 0.5);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		triangle.draw();
		glfwSwapBuffers(window);
	}
}