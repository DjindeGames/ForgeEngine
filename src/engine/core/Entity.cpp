#include "Entity.h"

#include "engine/3d/MeshComponent.h"
#include "engine/Core/Component.h"

#include <algorithm>

namespace ForgeEngine
{
	/*static*/ std::vector<Entity*> Entity::s_RegisteredEntities{};

	Entity::Entity()
	{
		m_Transform = new Transform();
	}

	/*static*/ Entity* Entity::RegisterEntity()
	{
		Entity* entity = new Entity{};
		s_RegisteredEntities.push_back(entity);
		return entity;
	}

	/*static*/ Entity* Entity::RegisterEntity(Entity* entity)
	{
		s_RegisteredEntities.push_back(entity);
		return entity;
	}

	/*static*/ void Entity::ReleaseEntities()
	{
		for (auto entity : s_RegisteredEntities)
		{
			entity->Destroy();
			delete(entity);
		}
		s_RegisteredEntities.clear();
	}

	Component* Entity::RegisterComponent(Component* component)
	{
		if (component != nullptr)
		{
			m_RegisteredComponents.push_back(component);
			component->SetOwner(this);
		}
		return component;
	}

	void Entity::UnregisterComponent(Component* component)
	{
		if (component != nullptr)
		{
			auto it = std::find(m_RegisteredComponents.begin(), m_RegisteredComponents.end(), component);
			if (it != m_RegisteredComponents.end() && *it != nullptr)
			{
				(*it)->OnDestroy();
				m_RegisteredComponents.erase(it);
				delete component;
			}
		}
	}
	
	/*static*/ void Entity::PreInit()
	{
		for (auto entity : s_RegisteredEntities)
		{
			if (entity != nullptr)
			{
				entity->OnPreInit();
			}
		}
	}

	/*static*/ void Entity::Init()
	{
		for (auto entity : s_RegisteredEntities)
		{
			if (entity != nullptr)
			{
				entity->OnInit();
			}
		}
	}

	/*static*/ void Entity::PostInit()
	{
		for (auto entity : s_RegisteredEntities)
		{
			if (entity != nullptr)
			{
				entity->OnPostInit();
			}
		}
	}

	/*static*/ void Entity::PreUpdate()
	{
		for (auto entity : s_RegisteredEntities)
		{
			if (entity != nullptr)
			{
				entity->OnPreUpdate();
			}
		}
	}

	/*static*/ void Entity::Update(float dT)
	{
		for (auto entity : s_RegisteredEntities)
		{
			if (entity != nullptr)
			{
				entity->OnUpdate(dT);
			}
		}
	}

	/*static*/ void Entity::PostUpdate()
	{
		for (auto entity : s_RegisteredEntities)
		{
			if (entity != nullptr)
			{
				entity->OnPostUpdate();
			}
		}
	}

	/*static*/ void Entity::DestroyEntity(ObjectID id)
	{
		auto it = std::find_if(s_RegisteredEntities.begin(), s_RegisteredEntities.end(), [&](const Entity * e) {if (e != nullptr && e->GetID() == id) return true; else return false; });
		if (it != s_RegisteredEntities.end() && (*it) != nullptr)
		{
			(*it)->Destroy();
			s_RegisteredEntities.erase(it);
		}
	}

	void Entity::OnPreInit() /*override*/
	{
		Mother::OnPreInit();
		for (auto component : m_RegisteredComponents)
		{
			if (component != nullptr)
			{
				component->OnPreInit();
			}
		}
	}

	void Entity::OnInit() /*override*/
	{
		Mother::OnInit();
		for (auto component : m_RegisteredComponents)
		{
			if (component != nullptr)
			{
				component->OnInit();
			}
		}
	}

	void Entity::OnPostInit() /*override*/
	{
		Mother::OnPostInit();
		for (auto component : m_RegisteredComponents)
		{
			if (component != nullptr)
			{
				component->OnPostInit();
			}
		}
	}

	void Entity::OnPreUpdate() /*override*/
	{
		Mother::OnPreUpdate();
		for (auto component : m_RegisteredComponents)
		{
			if (component != nullptr)
			{
				component->OnPreUpdate();
			}
		}
	}

	void Entity::OnUpdate(float dT) /*override*/
	{
		Mother::OnUpdate(dT);
		for (auto component : m_RegisteredComponents)
		{
			if (component != nullptr)
			{
				component->OnUpdate(dT);
			}
		}
	}

	void Entity::OnPostUpdate() /*override*/
	{
		Mother::OnPostUpdate();
		for (auto component : m_RegisteredComponents)
		{
			if (component != nullptr)
			{
				component->OnPostUpdate();
			}
		}
	}

	void Entity::Destroy()
	{
		OnDestroy();
	}

	void Entity::OnDestroy() /*override*/
	{
		Mother::OnDestroy();
		for (auto component : m_RegisteredComponents)
		{
			//TODO: Too much complexity
			UnregisterComponent(component);
		}
		delete m_Transform;
	}
}