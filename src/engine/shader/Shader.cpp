#include "Shader.h"

#include "engine/misc/Color.h"
#include "engine/shader/ShaderUtils.h"

#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <string>

namespace ForgeEngine
{
	Shader::Shader(const char* vsPath, const char* fsPath)
	{
		std::ifstream vertexShaderFile;
		std::ifstream fragmentShaderFile;

		std::stringstream vertexShaderStream;
		std::stringstream fragmentShaderStream;

		std::string vertexShaderSource{};
		std::string fragmentShaderSource{};

		// ensure ifstream objects can throw exceptions:
		vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try 
		{
			vertexShaderFile.open(vsPath);
			fragmentShaderFile.open(fsPath);

			vertexShaderStream << vertexShaderFile.rdbuf();
			fragmentShaderStream << fragmentShaderFile.rdbuf();

			vertexShaderFile.close();
			fragmentShaderFile.close();

			vertexShaderSource = vertexShaderStream.str();
			fragmentShaderSource = fragmentShaderStream.str();

			if (!ShaderUtils::TryCompileShader(m_VertexID, vertexShaderSource.c_str(), GL_VERTEX_SHADER) ||
				!ShaderUtils::TryCompileShader(m_FragmentID, fragmentShaderSource.c_str(), GL_FRAGMENT_SHADER) ||
				!ShaderUtils::TryLinkShaderProgram(m_ProgramID, true, &m_VertexID, &m_FragmentID))
			{
				std::cout << "Could not compile shaders!" << std::endl;
			}
		}
		catch (std::ifstream::failure failure)
		{
			std::cout << "Cannot open source path!" << std::endl;
		}
	}

	Shader::~Shader()
	{
		ShaderUtils::DeleteShaders(&m_VertexID, &m_FragmentID);
		ShaderUtils::DeletePrograms(&m_ProgramID);
	}

	void Shader::Use()
	{
		glUseProgram(m_ProgramID);
	}

	void Shader::SetFloat(const char* which, float value)
	{
		glUniform1f(glGetUniformLocation(m_ProgramID, which), value);
	}

	void Shader::SetBool(const char* which, bool value)
	{
		glUniform1i(glGetUniformLocation(m_ProgramID, which), static_cast<int>(value));
	}

	void Shader::SetInt(const char* which, int value)
	{
		glUniform1i(glGetUniformLocation(m_ProgramID, which), value);
	}

	void Shader::SetColor(const char* which, const Color& value)
	{
		glUniform4f(glGetUniformLocation(m_ProgramID, which), value.GetR(), value.GetG(), value.GetB(), value.GetA());
	}
}