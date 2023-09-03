#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <glad/glad.h>

#include "Config.hpp"
#include "Sandbox.hpp"

Sandbox::Sandbox()
{
	glViewport(0, 0, width, height);
	glClearColor(0, 0, 0, 0);

#if DEBUG
	m_shader = Shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
#else
	m_shader = Shader("vertex.glsl", "fragment.glsl");
	m_shader.bind();
#endif

	m_meshes.emplace_back(MeshType::Rect, 0.1, &m_shader);
	m_meshes.emplace_back(MeshType::Triangle, 0.1, &m_shader);
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

	ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("Meshes"))
		{
			if (ImGui::BeginMenu("Add"))
			{
				if (ImGui::MenuItem("Triangle"))
				{
					m_meshes.emplace_back(MeshType::Triangle, 0.5, &m_shader);
				}

				if (ImGui::MenuItem("Rectangle"))
				{
					m_meshes.emplace_back(MeshType::Rect, 0.5, &m_shader);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
	ImGui::EndMainMenuBar();

	ImGui::Begin("Objects");
		for (size_t i = 0; i < m_meshes.size(); i++)
		{
			ImGui::PushID(i);
			ImGui::Text("Meshe[%i]", i);
			ImGui::DragFloat3("Position", &m_meshes[i].transform.position.x, 0.01);
			ImGui::DragFloat3("Rotation", &m_meshes[i].transform.rotation.x, 0.01);
			ImGui::DragFloat3("Scale", &m_meshes[i].transform.scale.x, 0.01);
			ImGui::ColorEdit3("Color", &m_meshes[i].color.x);
			ImGui::Separator();
			ImGui::PopID();
		}
	ImGui::End();
}