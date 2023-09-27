#include <vector>

#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	const char* vertex = this->readContent(vertexPath);
	const char* fragment = this->readContent(fragmentPath);;
	std::uint32_t vertexID = glCreateShader(GL_VERTEX_SHADER);
	std::uint32_t fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexID, 1, &vertex, NULL);
	glShaderSource(fragmentID, 1, &fragment, NULL);

	this->compile(vertexID, "vertex");
	this->compile(fragmentID, "fragment");

	m_id = glCreateProgram();
	glAttachShader(m_id, vertexID);
	glAttachShader(m_id, fragmentID);
	glLinkProgram(m_id);
	
	checkLink(m_id);

	glDetachShader(m_id, vertexID);
	glDetachShader(m_id, fragmentID);
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

Shader::Shader(const char* computePath)
{
	const char* compute = readContent(computePath);
	std::uint32_t computeID = glCreateShader(GL_COMPUTE_SHADER);

	glShaderSource(computeID, 1, &compute, NULL);
	this->compile(computeID, "compute");

	m_id = glCreateProgram();
	glAttachShader(m_id, computeID);
	glLinkProgram(m_id);

	checkLink(m_id);

	glDetachShader(m_id, computeID);
	glDeleteShader(m_id, computeID);
}

void Shader::bind() const noexcept
{
	glUseProgram(m_id);
}

void Shader::checkLink(std::uint32 programID) 
{
	int linkStatus = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
	if (!linkStatus)
	{
		int length = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);

		std::vector<char> linkStatusMessage(length);
		glGetProgramInfoLog(programID, length, nullptr, linkStatusMessage.data());
		std::cout << "[ERROR] shader linking failed " << linkStatusMessage.data() << '\n';
		exit(0);
	}

	return true;
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
	std::string result = "";
	std::fstream fileReader(path);
	if (fileReader.is_open())
	{
		std::stringstream stream;
		stream << fileReader.rdbuf();
		result = stream.str();
	}
	else
	{
		std::cout << "[ERROR] shader at : " << path << " not found\n";
		exit(0);
	}

	return result.c_str();
}

void Shader::uniformMat4(const char* name, glm::mat4x4& m)
{
	glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, false, glm::value_ptr(m));
}

void Shader::uniformVec3(const char* name, glm::vec3& v)
{
	glUniform3fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(v));
}