#include <vector>

#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	const char* vertex = "";
	const char* fragment = "";
	std::uint32_t vertexID = glCreateShader(GL_VERTEX_SHADER);
	std::uint32_t fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	vertex = this->readContent(vertexPath);
	fragment = this->readContent(fragmentPath);

	glShaderSource(vertexID, 1, &vertex, NULL);
	glShaderSource(fragmentID, 1, &fragment, NULL);

	this->compile(vertexID, "vertex");
	this->compile(fragmentID, "fragment");

	std::uint32_t program = glCreateProgram();
	glAttachShader(program, vertexID);
	glAttachShader(program, fragmentID);
	glLinkProgram(program);

	glDetachShader(program, vertexID);
	glDetachShader(program, fragmentID);
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

void Shader::bind() const noexcept
{
	glUseProgram(m_id);
}

void Shader::compile(std::uint32_t id, std::string name)
{
	glCompileShader(id);

	int compileStatus;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus)
	{
		std::cout << "[ERROR] shader " << name << " compilation failed\n";

		auto length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		std::vector<char> messageError(length);
		glGetShaderInfoLog(id, length, nullptr, messageError.data());

		std::cout << messageError.data() << '\n';
		exit(0);
	}
}

const char* Shader::readContent(const char* path)
{
	const char* result = "";
	std::ifstream fileReader(path);
	if (fileReader.is_open())
	{
		std::stringstream stream;
		stream << fileReader.rdbuf();
		std::string string = stream.str();
		result = string.c_str();
	}
	else
	{
		std::cout << "[ERROR] shader at : " << path << " not found\n";
		exit(0);
	}

	return result;
}