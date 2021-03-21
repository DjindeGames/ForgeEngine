#include "ManagedObjectContainer.h"

#include <algorithm>

namespace ForgeEngine
{
	ManagedObject* ManagedObjectContainer::RegisterObject(ManagedObject* object)
	{
		m_RegisteredObjects.push_back(std::unique_ptr<ManagedObject>(object));
		return object;
	}

	ManagedObjectContainer::~ManagedObjectContainer()
	{
		OnDestroy();
	}

	void ManagedObjectContainer::OnDestroy()
	{
		for (auto& object : m_RegisteredObjects)
		{
			if (object != nullptr)
			{
				object->Destroy();
			}
		}
	}

	bool ManagedObjectContainer::PreInit()
	{
		for (auto& object : m_RegisteredObjects)
		{
			if (object != nullptr)
			{
				object->OnPreInit();
			}
		}
		return true;
	}

	bool ManagedObjectContainer::Init()
	{
		for (auto& object : m_RegisteredObjects)
		{
			if (object != nullptr)
			{
				object->OnInit();
			}
		}
		return true;
	}

	bool ManagedObjectContainer::PostInit()
	{
		for (auto& object : m_RegisteredObjects)
		{
			if (object != nullptr)
			{
				object->OnPostInit();
			}
		}
		return true;
	}

	void ManagedObjectContainer::PreUpdate(float dT)
	{
		unsigned int initializedObjectsThisFrame = 0;
		for (auto& object : m_RegisteredObjects)
		{
			if (object != nullptr)
			{
				if (object->IsInitialized())
				{
					object->OnPreUpdate(dT);
				}
				else if (object->NeedsPreInit() && initializedObjectsThisFrame < K_MAX_INITIALIZATIONS_PER_FRAME)
				{
					object->OnPreInit();
					initializedObjectsThisFrame++;
				}
			}
		}
	}

	void ManagedObjectContainer::Update(float dT)
	{
		unsigned int initializedObjectsThisFrame = 0;
		for (auto& object : m_RegisteredObjects)
		{
			if (object != nullptr)
			{
				if (object->IsInitialized())
				{
					object->OnUpdate(dT);
				}
				else if (object->NeedsInit() && initializedObjectsThisFrame < K_MAX_INITIALIZATIONS_PER_FRAME)
				{
					object->OnInit();
					initializedObjectsThisFrame++;
				}
			}
		}
	}

	void ManagedObjectContainer::PostUpdate(float dT)
	{
		unsigned int initializedObjectsThisFrame = 0;
		for (auto& object : m_RegisteredObjects)
		{
			if (object != nullptr)
			{
				if (object->IsInitialized())
				{
					object->OnPostUpdate(dT);
				}
				else if (object->NeedsPostInit() && initializedObjectsThisFrame < K_MAX_INITIALIZATIONS_PER_FRAME)
				{
					object->OnPostInit();
					initializedObjectsThisFrame++;
				}
			}
		}
	}

	void ManagedObjectContainer::DrawDebug(float dT)
	{
		for (auto& object : m_RegisteredObjects)
		{
			if (object != nullptr)
			{
				if (object->IsInitialized())
				{
					object->OnDrawDebug(dT);
				}
			}
		}
	}
}