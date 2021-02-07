#include "Entity.h"

#include <algorithm>

namespace ForgeEngine
{
	Component* Entity::RegisterComponent(Component* component)
	{
		if (component != nullptr)
		{
			m_RegisteredComponents.push_back(std::unique_ptr<Component>(component));
			component->SetOwner(this);
		}
		return component;
	}

	void Entity::OnPreInit() /*override*/
	{
		Mother::OnPreInit();
		for (auto& component : m_RegisteredComponents)
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
		for (auto& component : m_RegisteredComponents)
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
		for (auto& component : m_RegisteredComponents)
		{
			if (component != nullptr)
			{
				component->OnPostInit();
			}
		}
	}

	void Entity::OnPreUpdate() /*override*/
	{
		if (!IsActive())
		{
			return;
		}

		Mother::OnPreUpdate();

		for (auto& component : m_RegisteredComponents)
		{
			if (component != nullptr && component->IsActive())
			{
				component->OnPreUpdate();
			}
		}
	}

	void Entity::OnUpdate(float dT) /*override*/
	{
		if (!IsActive())
		{
			return;
		}

		Mother::OnUpdate(dT);

		for (auto& component : m_RegisteredComponents)
		{
			if (component != nullptr && component->IsActive())
			{
				component->OnUpdate(dT);
			}
		}
	}

	void Entity::OnPostUpdate() /*override*/
	{
		if (!IsActive())
		{
			return;
		}

		Mother::OnPostUpdate();

		m_Transform.Refresh();

		for (auto& component : m_RegisteredComponents)
		{
			if (component != nullptr && component->IsActive())
			{
				component->OnPostUpdate();
			}
		}
	}

	void Entity::OnDestroy() /*override*/
	{
		Mother::OnDestroy();
		for (auto& component : m_RegisteredComponents)
		{
			if (component != nullptr)
			{
				component->Destroy();
			}
		}
	}
}