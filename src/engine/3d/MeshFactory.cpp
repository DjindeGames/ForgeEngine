#include "MeshFactory.h"

#include "engine/math/Vector3.h"
#include "engine/shader/ShaderUtils.h"

namespace ForgeEngine
{
	namespace MeshFactory
	{
		std::vector<std::unique_ptr<Mesh>> m_Meshes{};

		Mesh* RegisterMesh(const std::vector<Vector3>& vertices, const std::vector<unsigned int>& indices, Shader* shader, const Color& renderColor /*= COLOR_RENDER_DEFAULT*/)
		{
			m_Meshes.push_back(std::make_unique<Mesh>(vertices, indices, shader, renderColor));
			return m_Meshes[m_Meshes.size() - 1].get();
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