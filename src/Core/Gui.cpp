#include <string>
#include <iostream>

#include <glad/glad.h>
#include <imgui/imgui.h>

#include "Gui.hpp"

Gui::Gui()
{
	auto version = glGetString(GL_VERSION);
	auto gpu = glGetString(GL_RENDERER);

	m_gpuName = "GPU : ";
	m_versionName = "Version : ";

	for (size_t i = 0; i < strlen((char*)gpu); i++)
	{
		m_gpuName += gpu[i];
	}

	for (size_t i = 0; i < strlen((char*)version); i++)
	{
		m_versionName += version[i];
	}

	m_mode = "Mode : Default";
#ifdef DEBUG
	m_mode = "Mode : Debug";
#elif RELEASE
	m_mode = "Mode : Release";
#endif
}

void Gui::settings(int fps)
{
	static const char* vn = m_versionName.c_str();
	static const char* gn = m_gpuName.c_str();

    ImGui::Begin("Settings");
		ImGui::TextUnformatted("Info");
		ImGui::Separator();
		ImGui::Text("FPS : %i", fps);
		ImGui::TextUnformatted(m_mode);
		ImGui::TextUnformatted(vn);
		ImGui::TextUnformatted(gn);
	ImGui::End();
}

void Gui::scene(std::vector<Mesh>& meshes)
{
    ImGui::Begin("Scene");
		ImGui::Text("Count : %i", meshes.size());
		ImGui::Separator();

		for (size_t i = 0; i < meshes.size(); i++)
		{
			char buffer[20];
			std::sprintf(buffer, "Meshes[%i]", i);		
			if (ImGui::CollapsingHeader(buffer))
			{
				ImGui::PushID(i);

				ImGui::TextUnformatted("Transform");
				ImGui::Separator();
				ImGui::DragFloat3("Position", &meshes[i].transform.position.x, 0.01);
				ImGui::DragFloat3("Rotation", &meshes[i].transform.rotation.x, 0.01);
				ImGui::DragFloat3("Scale", &meshes[i].transform.scale.x, 0.01);

				ImGui::TextUnformatted("Material");
				ImGui::Separator();
				ImGui::ColorEdit3("Color", &meshes[i].material.albedo.x);

				if (ImGui::BeginCombo("Render Type", Gui::RenderTypeStr(meshes[i].renderType)))
				{
					for (int j = static_cast<int>(RenderType::Color); j <= static_cast<int>(RenderType::Shader); j++)
					{
						RenderType current = static_cast<RenderType>(j);
						bool selected = meshes[i].renderType == current;
						if (ImGui::Selectable(Gui::RenderTypeStr(current), selected))
						{
							meshes[i].renderType = current;
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
					meshes[i].remove();
					meshes.erase(meshes.begin() + i);
				}

				ImGui::PopID();
			}		
		}
	ImGui::End();
}

void Gui::mainMenu(std::vector<Mesh>& meshes, Shader* shader)
{
    ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("Meshes"))
		{
			if (ImGui::BeginMenu("Add"))
			{
				if (ImGui::BeginMenu("2D"))
				{
					if (ImGui::MenuItem("Triangle"))
					{
						meshes.emplace_back(MeshType::Triangle, 0.1, shader);
					}

					if (ImGui::MenuItem("Rectangle"))
					{
						meshes.emplace_back(MeshType::Rect, 0.1, shader);
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
}

const char* Gui::RenderTypeStr(RenderType type)
{
    switch(type)
    {
        case RenderType::Color :
            return "Color";

        case RenderType::Texture :
            return "Texture";

        case RenderType::Shader :
            return "Shader";

        default :
            return "Unknown";
    }
}