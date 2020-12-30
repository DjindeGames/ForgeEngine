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

		void DeletePrograms(const GL_ID* programs, ...)
		{
			va_list args;
			va_start(args, programs);

			while (*programs) {
				glDeleteProgram(*programs);
				++programs;
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
	}
}