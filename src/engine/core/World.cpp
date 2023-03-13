#include "engine/core/World.h"

#include <algorithm>

namespace ForgeEngine
{
	Entity* World::RegisterEntity()
	{
        Entity* entity = new Entity(this);
		m_RegisteredEntities.push_back(Unique<Entity>(entity));
		return entity;
	}

    World::~World()
    {
        OnDestroy();
    }

	bool World::PreInit()
	{
		for (auto& entity : m_RegisteredEntities)
		{
			if (entity != nullptr)
			{
				entity->OnPreInit();
			}
		}
        for (auto& component : m_Components)
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
        return true;
	}

	bool World::Init()
	{
		for (auto& entity : m_RegisteredEntities)
		{
			if (entity != nullptr)
			{
				entity->OnInit();
			}
		}
        for (auto& component : m_Components)
        {
            if (component != nullptr)
            {
                if (!component->OnInit())
                {
                    //Should display warning here!
                    component->SetActive(false);
                }
            }
        }
		return true;
	}

	bool World::PostInit()
	{
		for (auto& entity : m_RegisteredEntities)
		{
			if (entity != nullptr)
			{
				entity->OnPostInit();
			}
		}
        for (auto& component : m_Components)
        {
            if (component != nullptr)
            {
                if (!component->OnPostInit())
                {
                    //Should display warning here!
                    component->SetActive(false);
                }
            }
        }
		return true;
	}

	void World::PreUpdate(float dT)
	{
		unsigned int initializedEntitiesThisFrame = 0;
		for (auto& entity : m_RegisteredEntities)
		{
			if (entity != nullptr)
			{
				if (entity->IsInitialized())
				{
					entity->OnPreUpdate(dT);
				}
				else if (entity->NeedsPreInit() && initializedEntitiesThisFrame < K_MAX_INITIALIZATIONS_PER_FRAME)
				{
					entity->OnPreInit();
					initializedEntitiesThisFrame++;
				}
			}
		}
        for (auto& component : m_Components)
        {
            if (component != nullptr)
            {
                component->OnPreUpdate(dT);
            }
        }
	}

	void World::Update(float dT)
	{
		unsigned int initializedEntitiesThisFrame = 0;
		for (auto& entity : m_RegisteredEntities)
		{
			if (entity != nullptr)
			{
				if (entity->IsInitialized())
				{
					entity->OnUpdate(dT);
				}
				else if (entity->NeedsInit() && initializedEntitiesThisFrame < K_MAX_INITIALIZATIONS_PER_FRAME)
				{
					entity->OnInit();
					initializedEntitiesThisFrame++;
				}
			}
		}
        for (auto& component : m_Components)
        {
            if (component != nullptr)
            {
                component->OnUpdate(dT);
            }
        }
	}

	void World::PostUpdate(float dT)
	{
		unsigned int initializedEntitiesThisFrame = 0;
		for (auto& entity : m_RegisteredEntities)
		{
			if (entity != nullptr)
			{
				if (entity->IsInitialized())
				{
					entity->OnPostUpdate(dT);
				}
				else if (entity->NeedsPostInit() && initializedEntitiesThisFrame < K_MAX_INITIALIZATIONS_PER_FRAME)
				{
					entity->OnPostInit();
					initializedEntitiesThisFrame++;
				}
			}
		}
        for (auto& component : m_Components)
        {
            if (component != nullptr)
            {
                component->OnPostUpdate(dT);
            }
        }
	}

	void World::DrawDebug(float dT) 
	{
		for (auto& entity : m_RegisteredEntities)
		{
			if (entity != nullptr)
			{
				if (entity->IsInitialized())
				{
					entity->OnDrawDebug(dT);
				}
			}
		}
        for (auto& component : m_Components)
        {
            if (component != nullptr)
            {
                component->OnDrawDebug(dT);
            }
        }
	}

	void World::OnDestroy()
	{
        for (auto& entity : m_RegisteredEntities)
        {
            if (entity != nullptr)
            {
                entity->Destroy();
            }
        }
		for (auto& component : m_Components)
		{
			if (component != nullptr)
			{
				component->Destroy();
			}
		}
	}
}