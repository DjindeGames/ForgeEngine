#pragma once

#include "engine/3d/Mesh.h"
#include "engine/core/CoreEngine.h"
#include "engine/misc/Color.h"
#include "engine/shader/Shader.h"

#include <memory>
#include <vector>

namespace ForgeEngine
{
	class Mesh;

	namespace MeshFactory
	{
		Mesh* RegisterMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, Shader* shader, const Color& renderColor = COLOR_RENDER_DEFAULT);
		void Update();
	}
}