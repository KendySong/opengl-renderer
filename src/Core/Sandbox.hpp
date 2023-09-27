#pragma once
#include "../Graphics/Mesh.hpp"

class Sandbox
{
public :
	Sandbox();
	void update(float deltaTime);
	void render();

private :
	Shader m_shader;
	std::vector<Mesh> m_meshes;
};