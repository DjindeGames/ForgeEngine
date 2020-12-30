#pragma once

#include "engine/3d/Mesh.h"
#include "engine/core/CoreEngine.h"
#include "engine/misc/Color.h"
#include "engine/shader/Shader.h"

#include <memory>
#include <vector>

namespace ForgeEngine
{
	class Vector3;
	
	namespace MeshFactory
	{
		void RegisterMesh(const std::vector<Vector3>& vertices, const std::vector<unsigned int>& indices, Shader* shader, Color renderColor = COLOR_RENDER_DEFAULT);
		void Update();
	}
}