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
	Shader() = default;
	Shader(Shader&) = delete;
	Shader(const char* vertexPath, const char* fragmentPath);
	Shader(const char* computePath);

	void bind() const noexcept;

private:
	void checkLink(std::uint32_t programID);
	void compile(std::uint32_t id, std::string name);
	const char* readContent(const char* path);

public :
	void uniformMat4(const char* name, const glm::mat4x4& m);
	void uniformVec3(const char* name, const glm::vec3& v);
	void uniformVec2(const char* name, const glm::vec2& v);
	void uniformI(const char* name, const int v);

private :
	std::uint32_t m_id;
};