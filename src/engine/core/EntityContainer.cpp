#include "EntityContainer.h"

#include "engine/core/Entity.h"

namespace ForgeEngine
{
	Entity* EntityContainer::RegisterEntity()
	{
		return static_cast<Entity*>(Mother::RegisterObject(new Entity{}));
	}
}
