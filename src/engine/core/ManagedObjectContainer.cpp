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

	void ManagedObjectContainer::PreInit()
	{
		for (auto& object : m_RegisteredObjects)
		{
			if (object != nullptr)
			{
				object->OnPreInit();
			}
		}
	}

	void ManagedObjectContainer::Init()
	{
		for (auto& object : m_RegisteredObjects)
		{
			if (object != nullptr)
			{
				object->OnInit();
			}
		}
	}

	void ManagedObjectContainer::PostInit()
	{
		for (auto& object : m_RegisteredObjects)
		{
			if (object != nullptr)
			{
				object->OnPostInit();
			}
		}
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