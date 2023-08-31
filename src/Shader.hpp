#pragma once
#include <string>

#include <glm/glm.hpp>


#include <fstream>
#include <windows.h>

#define BLUE 9
#define GREEN 10
#define LIGHT_BLUE 11
#define RED 12
#define PURPLE 13
#define YELLOW 14
#define WHITE 15

class Log
{
private:
	Log();

public:
	static Log* instance() noexcept;

	void log(std::string log, int color = 15);

private:
	static Log* s_log;
	HANDLE m_hConsole;
	std::ofstream m_logStream;
};

class Shader
{
public:
	Shader() = default;
	Shader(const char* vertexPath, const char* fragmentPath);

	void setMat4x4(const char* name, const glm::mat4x4& matrix);
	void setVec3(const char* name, const glm::vec3& vec);
	void setFloat(const char* name, float value);
	void setBool(const char* name, bool value);
	std::uint32_t getProgram() noexcept;

private:
	bool checkCompileStatus(std::uint32_t objectID, std::string name);
	std::pair<std::string, bool> loadShader(const char* shaderPath);

	std::uint32_t m_program;
};