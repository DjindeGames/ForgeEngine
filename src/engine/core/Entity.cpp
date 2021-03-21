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

	void Entity::OnPreUpdate(float dT) /*override*/
	{
		if (!IsActive())
		{
			return;
		}

		Mother::OnPreUpdate(dT);

		for (auto& component : m_RegisteredComponents)
		{
			if (component != nullptr && component->IsActive())
			{
				if (component->IsInitialized())
				{
					component->OnPreUpdate(dT);
				}
				else if (component->NeedsPreInit())
				{
					component->OnPreInit();
				}
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
				if (component->IsInitialized())
				{
					component->OnUpdate(dT);
				}
				else if (component->NeedsInit())
				{
					component->OnInit();
				}
			}
		}
	}

	void Entity::OnPostUpdate(float dT) /*override*/
	{
		if (!IsActive())
		{
			return;
		}

		Mother::OnPostUpdate(dT);

		m_Transform.Refresh();

		for (auto& component : m_RegisteredComponents)
		{
			if (component != nullptr && component->IsActive())
			{
				if (component->IsInitialized())
				{
					component->OnPostUpdate(dT);
				}
				else if (component->NeedsPostInit())
				{
					component->OnPostInit();
				}
			}
		}
	}

	void Entity::OnDrawDebug(float dT) /*override*/
	{
		if (!IsActive())
		{
			return;
		}

		Mother::OnDrawDebug(dT);

		for (auto& component : m_RegisteredComponents)
		{
			if (component != nullptr && component->IsActive())
			{
				if (component->IsInitialized())
				{
					component->OnDrawDebug(dT);
				}
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