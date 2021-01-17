#pragma once

#include "engine/core/Entity.h"
#include "engine/core/ManagedObject.h"

namespace ForgeEngine
{
	class Component : public ManagedObject
	{
		using Mother = ManagedObject;

		friend Component* Entity::RegisterComponent(Component* component);
		friend void Entity::UnregisterComponent(Component* component);

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		protected:
			Entity* m_Owner{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Entity* GetOwner() const { return m_Owner; }

		private:
			void SetOwner(Entity* owner) { m_Owner = owner; }
	};
}