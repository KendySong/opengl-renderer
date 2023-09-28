#include <memory>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <glm/gtc/random.hpp>

#include "Gui.hpp"
#include "../Config.hpp"
#include "../Graphics/Texture.hpp"
#include "Application.hpp"
#include "Sandbox.hpp"

Sandbox::Sandbox()
{
	glViewport(0, 0, width, height);
	glClearColor(0, 0, 0, 0);

#if DEBUG
	m_shader = Shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
#else
	m_shader = Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
#endif

	for (size_t i = 0; i < 1; i++)
	{
		m_meshes.emplace_back(MeshType::Rect, 0.1, &m_shader);
        m_meshes[i].transform.position = glm::vec3(glm::diskRand(1.0f), 0);

		m_meshes[i].texture = std::shared_ptr<Texture>(new Texture("../textures/wall.jpg"));
		m_meshes[i].renderType = RenderType::Texture;
	}
}

void Sandbox::update(float deltaTime)
{

}

void Sandbox::render()
{
	for (size_t i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i].draw();
	}

	m_gui.settings(Application::instance().infoFps);
	m_gui.mainMenu(m_meshes, &m_shader);
	m_gui.scene(m_meshes);
}