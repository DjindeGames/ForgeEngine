#include "Entity.h"

#include "engine/3d/Mesh.h"

namespace ForgeEngine
{
	/*static*/ std::vector<Entity*> Entity::s_Entities{};

	Entity::Entity() : m_Position{}
	{
		m_Transform = new Transform();
	}

	Entity::~Entity()
	{
		delete m_Mesh;
	}

	/*static*/ Entity* Entity::RegisterEntity()
	{
		Entity* entity = new Entity{};
		s_Entities.push_back(entity);
		return entity;
	}

	/*static*/ void Entity::Update(float dT)
	{
		for (auto entity : s_Entities)
		{
			if (entity != nullptr)
			{
				entity->UpdateInternal(dT);
			}
		}
	}

	/*static*/ void Entity::ReleaseEntities()
	{
		for (auto entity : s_Entities)
		{
			delete(entity);
		}
		s_Entities.clear();
	}

	void Entity::UpdateInternal(float dT)
	{
		if (m_Mesh != nullptr)
		{
			m_Mesh->Render(m_Transform);
		}
	}
}