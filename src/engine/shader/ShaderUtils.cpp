#include "ShaderUtils.h"

#include "engine/misc/Color.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdarg.h>

namespace ForgeEngine
{
	namespace ShaderUtils
	{
		#define LOG_SIZE 512

		#define VERTEX_SHADER_SOURCE_DEFAULT    "#version 330 core\n" \
												"layout (location = 0) in vec3 aPos;\n" \
												"void main()\n" \
												"{\n" \
												"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" \
												"}\0"

		#define FRAGMENT_SHADER_SOURCE_DEFAULT  "#version 330 core\n" \
												"out vec4 FragColor;\n" \
												"uniform vec4 renderColor;\n" \
												"void main()" \
												"{\n" \
												"	FragColor = renderColor;\n" \
												"}\n"

		GL_ID defaultVertexShader{}, defaultFragmentShader{}, defaultShaderProgram{};

		bool TryCompileShader(GL_ID& shader, const char* shaderSource, int shaderType, bool outputLogs /* = true*/)
		{
			//Compile shader
			shader = glCreateShader(shaderType);
			glShaderSource(shader, 1, &shaderSource, NULL);
			glCompileShader(shader);

			//Check if compilation was successful
			GL_RESULT compilationSuccess;
			char infoLog[LOG_SIZE];
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationSuccess);

			//Output log if needed
			if (!compilationSuccess && outputLogs)
			{
				glGetShaderInfoLog(shader, LOG_SIZE, nullptr, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			}

			return static_cast<bool>(compilationSuccess);
		}

		bool TryLinkShaderProgram(GL_ID& shaderProgram, bool outputLogs, const GL_ID* shaders, ...)
		{
			va_list args;

			//Creates shader program
			shaderProgram = glCreateProgram();

			//Links all shaders into the shaderProgram
			va_start(args, shaders);

			while (*shaders) {
				glAttachShader(shaderProgram, *shaders);
				++shaders;
			}

			va_end(args);

			glLinkProgram(shaderProgram);

			//Check if linking was successful
			GL_RESULT compilationSuccess;
			char infoLog[LOG_SIZE];
			glGetProgramiv(shaderProgram, GL_LINK_STATUS, &compilationSuccess);

			//Output log if needed
			if (!compilationSuccess && outputLogs)
			{
				glGetShaderInfoLog(shaderProgram, LOG_SIZE, nullptr, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			}

			return static_cast<bool>(compilationSuccess);
		}

		void DeleteShaders(const GL_ID* shaders, ...)
		{
			va_list args;
			va_start(args, shaders);

			while (*shaders) {
				glDeleteShader(*shaders);
				++shaders;
			}

			va_end(args);
		}

		void SetBackgroundColor(Color backgroundColor)
		{
			// set state color
			glClearColor(backgroundColor.GetR(), backgroundColor.GetG(), backgroundColor.GetB(), backgroundColor.GetA());
			// applies state
			glClear(GL_COLOR_BUFFER_BIT);
		}

		GL_ID GetDefaultShaderProgram()
		{
			if (defaultShaderProgram == GL_NULL_ID)
			{
				//Create and compile both vertex shader (geometry) and fragment shader (color) and links them into one shader program
				if (
					!TryCompileShader(defaultVertexShader, VERTEX_SHADER_SOURCE_DEFAULT, GL_VERTEX_SHADER) ||
					!TryCompileShader(defaultFragmentShader, FRAGMENT_SHADER_SOURCE_DEFAULT, GL_FRAGMENT_SHADER) ||
					!TryLinkShaderProgram(defaultShaderProgram, true, &defaultVertexShader, &defaultFragmentShader)
					)
				{
					return GL_NULL_ID;
				}
			}
			return defaultShaderProgram;
		}

		void ReleaseResources()
		{
			glDeleteProgram(defaultVertexShader);
			glDeleteProgram(defaultFragmentShader);
			glDeleteProgram(defaultShaderProgram);
		}
	}
}