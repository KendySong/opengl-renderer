#include <iostream>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Sandbox.hpp"
#include "Config.hpp"
#include "Timer.hpp"
#include "Application.hpp"

Application Application::m_application;

Application& Application::instance()
{
	return m_application;
}

int Application::run()
{
	Timer fpsClock;
	Timer deltaClock;
	std::uint32_t fps = 0;
	std::uint32_t infoFps = 0;

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

	std::string gpuName = "";
	std::string versionName = "";
	auto version = glGetString(GL_VERSION);
	auto gpu = glGetString(GL_RENDERER);
	for (size_t i = 0; i < strlen((char*)gpu); i++)
		gpuName += gpu[i];
	for (size_t i = 0; i < strlen((char*)version); i++)
		versionName += version[i];
	
	std::cout << "[INFO] " << version << '\n';
	std::cout << "[INFO] " << gpu << '\n';

	Sandbox sandbox;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	
		sandbox.update(deltaClock.getElapsedTime());
		deltaClock.restart();

		fps++;
		if (fpsClock.getElapsedTime() >= 1)
		{
			infoFps = fps;
			fps = 0;
			fpsClock.restart();
		}

		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		sandbox.render();

		ImGui::Begin("Info");
		ImGui::Text("FPS : %i", infoFps);
		ImGui::Text("Version : %s", versionName.c_str());
		ImGui::Text("GPU : %s", gpuName.c_str());
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	return 0;
}

Application::Application()
{

}