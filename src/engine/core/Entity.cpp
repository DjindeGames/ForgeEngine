#include "Entity.h"

#include "engine/3d/MeshComponent.h"
#include "engine/Core/Component.h"

#include <algorithm>

namespace ForgeEngine
{
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
		//m_Transform.ResetMatrix();
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

	void Entity::OnDestroy() /*override*/
	{
		Mother::OnDestroy();
		for (auto component : m_RegisteredComponents)
		{
			//TODO: Too much complexity
			UnregisterComponent(component);
		}
	}
}