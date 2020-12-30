#pragma once

#include "engine/core/CoreEngine.h"

namespace ForgeEngine
{
	#define DEFAULT_VERTEX_SHADER_PATH   "assets\\shaders\\vertex\\default.glslv"
	#define DEFAULT_FRAGMENT_SHADER_PATH "assets\\shaders\\fragment\\default.glslf"

	#define DEFAULT_RENDER_COLOR_NAME "renderColor"

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

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
			~Shader();

			void Use();

			//Use should be called before calling any of the following!
			void SetFloat(const char* which, float value);
			void SetBool(const char* which, bool value);
			void SetInt(const char* which, int value);
			void SetColor(const char* which, const Color& value);
	};
}