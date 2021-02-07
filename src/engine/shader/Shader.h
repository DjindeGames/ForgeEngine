#pragma once

#include "engine/core/CoreEngine.h"
#include "engine/math/Math.h"
#include "engine/core/Object.h"

#include <utility>
#include <vector>

namespace ForgeEngine
{
	#define GLSL_ATTRIBUTE_TOKEN "//ATTRIBUTE"

	#define DEFAULT_VERTEX_SHADER_PATH   "assets\\shaders\\vertex\\default.glslv"
	#define DEFAULT_FRAGMENT_SHADER_PATH "assets\\shaders\\fragment\\default.glslf"

	#define TEXTURED_VERTEX_SHADER_PATH   "assets\\shaders\\vertex\\textured.glslv"
	#define TEXTURED_FRAGMENT_SHADER_PATH "assets\\shaders\\fragment\\textured.glslf"

	#define DEFAULT_RENDER_COLOR_NAME "RenderColor"
	#define DEFAULT_RENDER_TEXTURE_NAME "RenderTexture"
	#define DEFAULT_TRANSFORM_NAME "Transform"

	class Color;
	class Texture;
	class Transform;

	class Shader : Object
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			GL_ID m_ProgramID{};
			GL_ID m_VertexID{};
			GL_ID m_FragmentID{};

			//Stores the attributes declared in the shader source using the GLSL_ATTRIBUTE_TOKEN (must be declared in the right order !
			std::vector<unsigned int> m_AttributesSizes{};

			mutable int m_InputDataSize{-1};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
			~Shader();

			void Use();

			int GetInputDataSize() const;

			size_t GetNBAttributes() const { return m_AttributesSizes.size(); }
			unsigned int GetAttributeSize(int index) const;
			const auto& GetAttributesSizes() const { return m_AttributesSizes; }

			//Use should be called before calling any of the following!
			void SetFloat(const char* which, float value);
			void SetBool(const char* which, bool value);
			void SetInt(const char* which, int value);
			void SetColor(const char* which, const Color& value);
			void SetTexture(unsigned int which, const Texture* texture);
			void SetTransform(const char* which, const Transform* transform);
	};
}