#include "Shader.h"

#include "engine/core/ForgeEngine.h"
#include "engine/misc/Texture.h"
#include "engine/shader/ShaderUtils.h"
#include "system/misc/Color.h"
#include "system/misc/Utils.h"

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <numeric>
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

			std::vector<std::string> extractedLines = ForgeUtils::ExtractLines(GLSL_ATTRIBUTE_TOKEN, vertexShaderSource);
			for (const std::string& str : extractedLines)
			{
				std::vector<std::string> splitted = ForgeUtils::Split(" ", str);
				if (splitted.size() == 2)
				{
					m_AttributesSizes.push_back(std::stoi(splitted[1]));
				}
			}

			if (!ShaderUtils::TryCompileShader(m_VertexID, vsPath, vertexShaderSource.c_str(), GL_VERTEX_SHADER) ||
				!ShaderUtils::TryCompileShader(m_FragmentID, fsPath, fragmentShaderSource.c_str(), GL_FRAGMENT_SHADER) ||
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

	int Shader::GetInputDataSize() const
	{
		if (m_InputDataSize == -1)
		{
			m_InputDataSize = std::accumulate(m_AttributesSizes.begin(), m_AttributesSizes.end(), 0);
		}
		return m_InputDataSize;
	}

	unsigned int Shader::GetAttributeSize(int index) const
	{
		if (index < m_AttributesSizes.size())
		{
			return m_AttributesSizes[index];
		}
		return -1;
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
		glUniform4f(glGetUniformLocation(m_ProgramID, which), value.GetRRatio(), value.GetGRatio(), value.GetBRatio(), value.GetA());
	}

	void Shader::SetTexture(unsigned int which, const Texture* texture)
	{
		if (texture != nullptr)
		{
			glActiveTexture(which); // activate the texture unit first before binding texture
			glBindTexture(GL_TEXTURE_2D, texture->GetGLTexture());
		}
	}

	void Shader::SetTransform(const char* which, const TransformComponent& transform)
	{
        glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, which), 1, GL_FALSE, glm::value_ptr(transform.GetMatrix()));
	}

	void Shader::SetProjection(const char* which, const Matrix4& projection)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, which), 1, GL_FALSE, glm::value_ptr(projection));
	}

	void Shader::SetView(const char* which, const Matrix4& view)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, which), 1, GL_FALSE, glm::value_ptr(view));
	}

    void Shader::SetVector4(const char* which, const Vector3& vector)
    {
        glUniform4f(glGetUniformLocation(m_ProgramID, which), vector.x, vector.y, vector.z, 0.f);
    }
}