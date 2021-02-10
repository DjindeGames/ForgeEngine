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

	void ManagedObjectContainer::PreUpdate()
	{
		for (auto& object : m_RegisteredObjects)
		{
			if (object != nullptr)
			{
				object->OnPreUpdate();
			}
		}
	}

	void ManagedObjectContainer::Update(float dT)
	{
		for (auto& object : m_RegisteredObjects)
		{
			if (object != nullptr)
			{
				object->OnUpdate(dT);
			}
		}
	}

	void ManagedObjectContainer::PostUpdate()
	{
		for (auto& object : m_RegisteredObjects)
		{
			if (object != nullptr)
			{
				object->OnPostUpdate();
			}
		}
	}
}