#pragma once

#include "engine/3d/Mesh.h"
#include "engine/core/CoreEngine.h"
#include "engine/misc/Color.h"

#include <memory>
#include <vector>

namespace ForgeEngine
{
	class Vector3;
	
	namespace MeshFactory
	{
		void RegisterMesh(const std::vector<Vector3>& vertices, const std::vector<unsigned int>& indices = std::vector<unsigned int>{}, Color renderColor = COLOR_MAGENTA);
		void RegisterMesh(const std::vector<Vector3>& vertices, Color renderColor = COLOR_MAGENTA);
		void Update();
	}
}