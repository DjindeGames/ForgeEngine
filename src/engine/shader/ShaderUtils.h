#pragma once

#include "engine/core/Defines.h"
#include "engine/shader/Shader.h"

namespace ForgeEngine
{
	class Color;

	namespace ShaderUtils
	{
		bool TryCompileShader(GL_ID& shader, const char* shaderSource, int shaderType, bool outputLogs = true);
		bool TryLinkShaderProgram(GL_ID& shaderProgram, bool outputLogs, const GL_ID* shaders, ...);
		void DeleteShaders(const GL_ID* shaders, ...);
		void DeletePrograms(const GL_ID* programs, ...);

		void ClearScreen(Color backgroundColor);
	}
}