#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

class Shader
{
public :
	Shader(Shader&) = delete;
	Shader(const char* vertexPath, const char* fragmentPath);
	void bind() const noexcept;

private :
	void compile(std::uint32_t id, std::string name);
	const char* readContent(const char* path);

	std::uint32_t m_id;
};