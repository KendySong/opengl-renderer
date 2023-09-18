#include "MenuNode.hpp"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <iostream>

MenuNode::MenuNode(const char* name)
{
	m_name = name;
}

MenuNode::MenuNode(const char* name, std::function<void()> action) : action(action)
{
	m_name = name;
}

void MenuNode::display()
{
	if (ImGui::BeginMenu(m_name))
	{
		if (ImGui::BeginMenu("Add"))
		{
			if (ImGui::BeginMenu("2D"))
			{
				if (ImGui::MenuItem("Triangle"))
				{
					
				}

				if (ImGui::MenuItem("Rectangle"))
				{
					
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
}