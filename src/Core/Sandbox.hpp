#pragma once
#include "Gui.hpp"
#include "../Graphics/Mesh.hpp"

class Sandbox
{
public :
	Sandbox();
	void update(float deltaTime);
	void render();

private :
	Gui m_gui;
	Shader m_shader;
	std::vector<Mesh> m_meshes;
};