#include "MeshFactory.h"

#include "engine/math/Vector3.h"

namespace ForgeEngine
{
	/*static*/ std::vector<std::unique_ptr<Mesh>> MeshFactory::m_Meshes{};

	/*static*/ void MeshFactory::CreateMesh(const std::vector<Vector3>& vertices, GL_ID shaderProgram, const std::vector<unsigned int>& indices/*= std::vector<unsigned int>{}*/)
	{
		m_Meshes.push_back(std::make_unique<Mesh>(vertices, shaderProgram, indices));
	}

	/*static*/ void MeshFactory::Update()
	{
		for (const std::unique_ptr<Mesh>& mesh : m_Meshes)
		{
			mesh.get()->Render();
		}
	}
}