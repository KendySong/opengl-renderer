#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(Shader&) = delete;
	Shader(const char* vertexPath, const char* fragmentPath);
	void bind() const noexcept;

private:
	void compile(std::uint32_t id, std::string name);
	const char* readContent(const char* path);

public :
	void uniformMat4(const char* name, glm::mat4x4& m);
	void uniformVec3(const char* name, glm::vec3& v);

private :
	std::uint32_t m_id;
};