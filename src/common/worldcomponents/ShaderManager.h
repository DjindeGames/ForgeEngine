#pragma once

#include "engine/core/WorldComponent.h"
#include "engine/shader/Shader.h"

#include <unordered_map>

namespace ForgeEngine
{
	enum class EShaderType
	{
		Default = 0,
		Textured,
		Lit,
		Count
	};

	class ShaderManager : public WorldComponent
	{
		using Mother = WorldComponent;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			std::unordered_map<EShaderType, Unique<Shader>> m_RegisteredShaders{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			ShaderManager();

			Shader* GetShaderByType(EShaderType shaderType) const;
	};
}