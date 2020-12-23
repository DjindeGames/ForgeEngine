#pragma once

#include "engine/3d/Mesh.h"
#include "engine/core/CoreEngine.h"

#include <memory>
#include <vector>

namespace ForgeEngine
{
	class Vector3;

	class MeshFactory
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			static std::vector<std::unique_ptr<Mesh>> m_Meshes;

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			static void CreateMesh(const std::vector<Vector3>& vertices, GL_ID shaderProgram, const std::vector<unsigned int>& indices = std::vector<unsigned int>{});
			static void Update();
	};
}