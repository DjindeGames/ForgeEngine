#pragma once

#include "engine/core/CoreEngine.h"

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
			unsigned int m_NumIndices{};
			GL_ID m_ShaderProgram{};
			GL_ID m_VertexArrayObject{};
			GL_ID m_VertexBufferObject{};
			GL_ID m_VertexBufferElement{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Mesh(const std::vector<Vector3>& vertices, GL_ID shaderProgram, const std::vector<unsigned int>& indices = std::vector<unsigned int>{});
			//This should probably be done !
			//Mesh(const Mesh& mesh) = delete;
			~Mesh();

			void Render() const;

		private:
			void InitRender(const std::vector<Vector3>& vertices, GL_ID shaderProgram, const std::vector<unsigned int>& indices);
	};
}