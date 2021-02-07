#include "ShaderManager.h"

#include "engine/shader/Shader.h"

namespace ForgeEngine
{
	ShaderManager::ShaderManager() :
		Mother()
	{
		//Default
		m_RegisteredShaders[EShaderType::Default] = std::make_unique<Shader>(DEFAULT_VERTEX_SHADER_PATH, DEFAULT_FRAGMENT_SHADER_PATH);

		//Textured
		m_RegisteredShaders[EShaderType::Textured] = std::make_unique<Shader>(TEXTURED_VERTEX_SHADER_PATH, TEXTURED_FRAGMENT_SHADER_PATH);
	}
}