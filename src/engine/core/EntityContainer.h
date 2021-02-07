#pragma once

#include "engine/core/ManagedObjectContainer.h"
#include "engine/core/Singleton.h"

namespace ForgeEngine
{
	class Entity;

	class EntityContainer : public ManagedObjectContainer, public Singleton<EntityContainer>
	{
		using Mother = ManagedObjectContainer;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Entity* RegisterEntity();
	};
}