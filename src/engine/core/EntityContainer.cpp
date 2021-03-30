#include "EntityContainer.h"

#include "engine/core/ForgeEngine.h"

namespace ForgeEngine
{
	Entity* EntityContainer::RegisterEntity()
	{
		Entity* entity = static_cast<Entity*>(Mother::RegisterObject(new Entity{}));
		entity->RegisterComponent(new TransformComponent{});
		return entity;
	}
}
