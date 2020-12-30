#include "MeshFactory.h"

#include "engine/math/Vector3.h"

namespace ForgeEngine
{
	namespace MeshFactory
	{
		std::vector<std::unique_ptr<Mesh>> m_Meshes{};

		void RegisterMesh(const std::vector<Vector3>& vertices, const std::vector<unsigned int>& indices/*= std::vector<unsigned int>{}*/, Color renderColor /*= COLOR_MAGENTA*/)
		{
			m_Meshes.push_back(std::make_unique<Mesh>(vertices, indices, renderColor));
		}

		void RegisterMesh(const std::vector<Vector3>& vertices, Color renderColor /*= COLOR_MAGENTA*/)
		{
			m_Meshes.push_back(std::make_unique<Mesh>(vertices, renderColor));
		}

		void Update()
		{
			for (const std::unique_ptr<Mesh>& mesh : m_Meshes)
			{
				mesh.get()->Render();
			}
		}
	}
}