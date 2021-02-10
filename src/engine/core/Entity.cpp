#include "Entity.h"

#include <algorithm>

namespace ForgeEngine
{
	bool Entity::OnPreInit() /*override*/
	{
		bool success = Mother::OnPreInit();
		for (auto& component : m_RegisteredComponents)
		{
			if (component != nullptr)
			{
				if (!component->OnPreInit())
				{
					//Should display warning here!
					component->SetActive(false);
				}
			}
		}
		return success;
	}

	bool Entity::OnInit() /*override*/
	{
		bool success = Mother::OnInit();
		for (auto& component : m_RegisteredComponents)
		{
			if (component != nullptr && component->IsActive())
			{
				if (!component->OnInit())
				{
					//Should display warning here!
					component->SetActive(false);
				}
			}
		}
		return success;
	}

	bool Entity::OnPostInit() /*override*/
	{
		bool success = Mother::OnPostInit();
		for (auto& component : m_RegisteredComponents)
		{
			if (component != nullptr && component->IsActive())
			{
				if (!component->OnPostInit())
				{
					//Should display warning here!
					component->SetActive(false);
				}
			}
		}
		return success;
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