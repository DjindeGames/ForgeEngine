#pragma once

#include "engine/core/Manager.h"
#include "engine/shader/Shader.h"

#include <unordered_map>

namespace ForgeEngine
{
	enum class EShaderType
	{
		Default = 0,
		Textured,
		Count
	};

	class ShaderManager : public Manager
	{
		using Mother = Manager;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			std::unordered_map<EShaderType, std::unique_ptr<Shader>> m_RegisteredShaders{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			ShaderManager();

			Shader* GetShaderByType(EShaderType shaderType) const;
	};
}