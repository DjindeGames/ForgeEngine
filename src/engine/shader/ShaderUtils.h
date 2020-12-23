#pragma once

#include "engine/core/CoreEngine.h"

namespace ForgeEngine
{
	class Color;

	bool TryCompileShader(GL_ID& shader, const char* shaderSource, int shaderType, bool outputLogs = true);
	bool TryLinkShaderProgram(GL_ID& shaderProgram, bool outputLogs, const GL_ID* shaders, ...);
	void DeleteShaders(const GL_ID* shaders, ...);

	void SetBackgroundColor(Color backgroundColor);
}