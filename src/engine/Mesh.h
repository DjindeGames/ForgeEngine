#pragma once

#include "CoreEngine.h"

#include <vector>

namespace ForgeEngine
{
	class Vector3;

	//A mesh is built using a collection of Vector3 that represents its vertices
	//Those vertices are converted into an array of floats to match openGL behaviour
	class Mesh
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			unsigned int m_NumVertices{};
			GL_ID m_ShaderProgram{};
			GL_ID m_VertexArrayObject{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Mesh(const std::vector<Vector3>& vertices, GL_ID shaderProgram);

			void Render();
	};
}