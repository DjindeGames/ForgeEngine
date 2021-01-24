#include "ManagedObjectContainer.h"

#include "engine/core/ManagedObject.h"

#include <algorithm>

namespace ForgeEngine
{
	ManagedObject* ManagedObjectContainer::RegisterObject(ManagedObject* object)
	{
		s_RegisteredObjects.push_back(object);
		return object;
	}

	void ManagedObjectContainer::DestroyObject(ObjectID id)
	{
		auto it = std::find_if(s_RegisteredObjects.begin(), s_RegisteredObjects.end(), [&](const ManagedObject* e) {if (e != nullptr && e->GetID() == id) return true; else return false; });
		if (it != s_RegisteredObjects.end() && (*it) != nullptr)
		{
			(*it)->Destroy();
			s_RegisteredObjects.erase(it);
		}
	}

	void ManagedObjectContainer::ReleaseObjects()
	{
		for (auto object : s_RegisteredObjects)
		{
			object->Destroy();
			delete(object);
		}
		s_RegisteredObjects.clear();
	}

	void ManagedObjectContainer::PreInit()
	{
		for (auto object : s_RegisteredObjects)
		{
			if (object != nullptr)
			{
				object->OnPreInit();
			}
		}
	}

	void ManagedObjectContainer::Init()
	{
		for (auto object : s_RegisteredObjects)
		{
			if (object != nullptr)
			{
				object->OnInit();
			}
		}
	}

	void ManagedObjectContainer::PostInit()
	{
		for (auto object : s_RegisteredObjects)
		{
			if (object != nullptr)
			{
				object->OnPostInit();
			}
		}
	}

	void ManagedObjectContainer::PreUpdate()
	{
		for (auto object : s_RegisteredObjects)
		{
			if (object != nullptr)
			{
				object->OnPreUpdate();
			}
		}
	}

	void ManagedObjectContainer::Update(float dT)
	{
		for (auto object : s_RegisteredObjects)
		{
			if (object != nullptr)
			{
				object->OnUpdate(dT);
			}
		}
	}

	void ManagedObjectContainer::PostUpdate()
	{
		for (auto object : s_RegisteredObjects)
		{
			if (object != nullptr)
			{
				object->OnPostUpdate();
			}
		}
	}
}