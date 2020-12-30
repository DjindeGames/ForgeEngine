#pragma once

#include "engine/core/CoreEngine.h"
#include "engine/misc/Color.h"
#include "engine/shader/Shader.h"

#include <vector>

namespace ForgeEngine
{
	class Shader;
	class Vector3;

	//!!! ALL MESHES SHOULD BE CREATED USING MESH FACTORY !!!
	//A mesh is built using a collection of Vector3 that represents its vertices
	//Those vertices are converted into an array of floats to match openGL behaviour
	class Mesh
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			Shader* m_Shader{};
			Color m_renderColor;

			GL_ID m_VertexArrayObject{};
			GL_ID m_VertexBufferObject{};
			GL_ID m_VertexBufferElement{};

			std::vector<unsigned int> m_Indices{};
			std::vector<Vector3> m_Vertices{};
			unsigned int m_NumVertices{};
			unsigned int m_NumIndices{};

			bool m_IsInitialized{ false };

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Mesh(const std::vector<Vector3>& vertices, const std::vector<unsigned int>& indices, Shader* shader, Color renderColor = COLOR_RENDER_DEFAULT);
			//This should probably be done !
			//Mesh(const Mesh& mesh) = delete;
			~Mesh();

			void Render();

		private:
			void InitRender();
	};
}