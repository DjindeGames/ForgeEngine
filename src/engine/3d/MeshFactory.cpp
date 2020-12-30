#include "MeshFactory.h"

#include "engine/math/Vector3.h"
#include "engine/shader/ShaderUtils.h"

namespace ForgeEngine
{
	namespace MeshFactory
	{
		std::vector<std::unique_ptr<Mesh>> m_Meshes{};

		void RegisterMesh(const std::vector<Vector3>& vertices, const std::vector<unsigned int>& indices, Shader* shader, Color renderColor /*= COLOR_RENDER_DEFAULT*/)
		{
			m_Meshes.push_back(std::make_unique<Mesh>(vertices, indices, shader, renderColor));
		}

		void Update()
		{
			for (const std::unique_ptr<Mesh>& mesh : m_Meshes)
			{
				if (Mesh* meshPtr = mesh.get())
				{
					meshPtr->Render();
				}
			}
		}
	}
}