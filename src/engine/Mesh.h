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
			float* m_Vertices{};
			unsigned int m_NumVertices{};
			GL_ID m_ShaderProgram{};
			GL_ID m_VertexArrayObject{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Mesh(Vector3 vertices[], unsigned int numVertices, GL_ID shaderProgram);
			Mesh(float vertices[], unsigned int numVertices, GL_ID shaderProgram);
			~Mesh();

			void Render();
	};
}