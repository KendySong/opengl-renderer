#include <memory>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <glad/glad.h>

#include "../Config.hpp"
#include "../Graphics/Texture.hpp"
#include "Sandbox.hpp"
#include "Gui.hpp"

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
		m_meshes.emplace_back(MeshType::Rect, 0.5, &m_shader);
		m_meshes[i].texture = std::shared_ptr<Texture>(new Texture("textures/wall.jpg"));
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
			
	ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("Meshes"))
		{
			if (ImGui::BeginMenu("Add"))
			{
				if (ImGui::BeginMenu("2D"))
				{
					if (ImGui::MenuItem("Triangle"))
					{
						m_meshes.emplace_back(MeshType::Triangle, 0.1, &m_shader);
					}

					if (ImGui::MenuItem("Rectangle"))
					{
						m_meshes.emplace_back(MeshType::Rect, 0.1, &m_shader);
					}
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("3D"))
				{
					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}
		
			ImGui::EndMenu();
		}
	ImGui::EndMainMenuBar();

	ImGui::Begin("Scene");
		ImGui::Text("Count : %i", m_meshes.size());
		ImGui::Separator();

		for (size_t i = 0; i < m_meshes.size(); i++)
		{
			char buffer[20];
			std::sprintf(buffer, "Meshes[%i]", i);		
			if (ImGui::CollapsingHeader(buffer))
			{
				ImGui::PushID(i);

				ImGui::TextUnformatted("Transform");
				ImGui::Separator();
				ImGui::DragFloat3("Position", &m_meshes[i].transform.position.x, 0.01);
				ImGui::DragFloat3("Rotation", &m_meshes[i].transform.rotation.x, 0.01);
				ImGui::DragFloat3("Scale", &m_meshes[i].transform.scale.x, 0.01);

				ImGui::TextUnformatted("Material");
				ImGui::Separator();
				ImGui::ColorEdit3("Color", &m_meshes[i].material.albedo.x);

				if (ImGui::BeginCombo("Render Type", Gui::RenderTypeStr(m_meshes[i].renderType)))
				{
					for (int j = static_cast<int>(RenderType::Color); j <= static_cast<int>(RenderType::Shader); j++)
					{
						RenderType current = static_cast<RenderType>(j);
						bool selected = m_meshes[i].renderType == current;
						if (ImGui::Selectable(Gui::RenderTypeStr(current), selected))
						{
							m_meshes[i].renderType = current;
						}
						
						if (selected) 
						{
							ImGui::SetItemDefaultFocus();
						}
					}	
					ImGui::EndCombo();		
				}
	
				ImGui::Separator();

				if (ImGui::Button("Delete"))
				{
					m_meshes[i].remove();
					m_meshes.erase(m_meshes.begin() + i);
				}

				ImGui::PopID();
			}		
		}
	ImGui::End();
}