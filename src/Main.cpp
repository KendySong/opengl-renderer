#include <cmath>
#include <array>
#include <vector>
#include <string>
#include <iostream>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

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
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Renderer", NULL, NULL);
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	std::cout << "[INFO] " << glGetString(GL_VERSION) << '\n';
	std::cout << "[INFO] " << glGetString(GL_VENDOR) << '\n';

	glViewport(0, 0, width, height);
	glClearColor(0, 0, 0, 0);

#if DEBUG
	Shader shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
	shader.bind();
#else
	Shader shader("vertex.glsl", "fragment.glsl");
	shader.bind();
#endif

	std::vector<Mesh> meshes;
	meshes.emplace_back(MeshType::Rect, 0.1, &shader);
	meshes.emplace_back(MeshType::Triangle, 0.1, &shader);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		for (size_t i = 0; i < meshes.size(); i++)
		{
			meshes[i].draw();
		}	

		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("Meshes"))
		{
			if (ImGui::BeginMenu("Add"))
			{
				if (ImGui::MenuItem("Triangle"))
				{
					meshes.emplace_back(MeshType::Triangle, 0.5, &shader);
				}

				if (ImGui::MenuItem("Rectangle"))
				{
					meshes.emplace_back(MeshType::Rect, 0.5, &shader);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
			
		ImGui::EndMainMenuBar();

		ImGui::Begin("Objects");
		for (size_t i = 0; i < meshes.size(); i++)
		{
			ImGui::PushID(i);
			ImGui::Text("Meshe[%i]", i);
			ImGui::DragFloat3("Position", &meshes[i].transform.position.x, 0.01);
			ImGui::DragFloat3("Rotation", &meshes[i].transform.rotation.x, 0.01);
			ImGui::DragFloat3("Scale", &meshes[i].transform.scale.x, 0.01);
			ImGui::ColorEdit3("Color", &meshes[i].color.x);
			ImGui::Separator();
			ImGui::PopID();
		}
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
}