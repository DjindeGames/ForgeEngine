#include "EntityContainer.h"

#include "engine/core/Entity.h"

namespace ForgeEngine
{
	Entity* EntityContainer::RegisterEntity()
	{
		return static_cast<Entity*>(Mother::RegisterObject(new Entity{}));
	}

	Entity* EntityContainer::RegisterEntity(Entity* entity)
	{
		return static_cast<Entity*>(Mother::RegisterObject(entity));
	}

	void EntityContainer::ReleaseEntities()
	{
		Mother::ReleaseObjects();
	}
}
