#pragma once

#include "engine/core/CoreEngine.h"
#include "engine/misc/Color.h"

#include <vector>

namespace ForgeEngine
{
	class Vector3;

	//A mesh is built using a collection of Vector3 that represents its vertices
	//Those vertices are converted into an array of floats to match openGL behaviour
	class Mesh
	{
		/*
		
		//Basic vertex shader code (written in GLSL)
		const char* vertexShaderSource =
			"#version 330 core\n"
			//This location = 0 is still a bit mysterious...
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";

		//Basic fragment shader code (written in GLSL)
		const char* fragmentShaderSource =
			"#version 330 core\n"
			"out vec4 FragColor;\n"
			"uniform vec4 renderColor;\n"
			"void main()"
			"{\n"
			"	FragColor = renderColor;\n"
			"}\n";

		*/

		

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			unsigned int m_NumVertices{};
			unsigned int m_NumIndices{};
			GL_ID m_ShaderProgram{};
			GL_ID m_VertexArrayObject{};
			GL_ID m_VertexBufferObject{};
			GL_ID m_VertexBufferElement{};

			std::vector<unsigned int> m_Indices{};
			std::vector<Vector3> m_Vertices{};
			Color m_renderColor;

			bool m_IsInitialized{ false };

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Mesh(const std::vector<Vector3>& vertices, const std::vector<unsigned int>& indices = std::vector<unsigned int>{}, Color renderColor = COLOR_MAGENTA);
			Mesh(const std::vector<Vector3>& vertices, Color renderColor = COLOR_MAGENTA);
			//This should probably be done !
			//Mesh(const Mesh& mesh) = delete;
			~Mesh();

			void Render();

		private:
			void InitRender();
	};
}