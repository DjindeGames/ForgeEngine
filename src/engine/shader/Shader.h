#pragma once

#include "engine/core/CoreEngine.h"

#include <utility>
#include <vector>

namespace ForgeEngine
{
	#define GLSL_ATTRIBUTE_TOKEN "//ATTRIBUTE"

	#define DEFAULT_VERTEX_SHADER_PATH   "assets\\shaders\\vertex\\default.glslv"
	#define DEFAULT_FRAGMENT_SHADER_PATH "assets\\shaders\\fragment\\default.glslf"

	#define TEXTURED_VERTEX_SHADER_PATH   "assets\\shaders\\vertex\\textured.glslv"
	#define TEXTURED_FRAGMENT_SHADER_PATH "assets\\shaders\\fragment\\textured.glslf"

	#define DEFAULT_RENDER_COLOR_NAME "renderColor"
	#define DEFAULT_RENDER_TEXTURE_NAME "renderTexture"

	class Color;

	class Shader
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			GL_ID m_ProgramID{};
			GL_ID m_VertexID{};
			GL_ID m_FragmentID{};

			//Attribute<index,size>
			std::vector<std::pair<unsigned int, unsigned int>> m_Attributes{};

			mutable int m_InputDataSize{-1};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
			~Shader();

			void Use();

			int GetInputDataSize() const;

			unsigned int GetNBAttributes() const { return m_Attributes.size(); }
			bool TryGetAttribute(int index, std::pair<unsigned int, unsigned int>& attribute) const;
			const auto& GetAttributes() const { return m_Attributes; }

			//Use should be called before calling any of the following!
			void SetFloat(const char* which, float value);
			void SetBool(const char* which, bool value);
			void SetInt(const char* which, int value);
			void SetColor(const char* which, const Color& value);
	};
}