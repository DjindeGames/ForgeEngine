#pragma once

#include "engine/math/Math.h"
#include "engine/math/Transform.h"
#include "engine/core/EntityContainer.h"
#include "engine/core/ManagedObject.h"

#include <vector>

namespace ForgeEngine
{
	class Component;

	class Entity : public ManagedObject
	{
		using Mother = ManagedObject;

		friend Entity* EntityContainer::RegisterEntity();
		friend Entity* EntityContainer::RegisterEntity(Entity* entity);

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			Transform m_Transform{};

			std::vector<Component*> m_RegisteredComponents;

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Transform& GetTransform() { return m_Transform; }
			void SetTransform(const Transform& transform) { m_Transform = transform; }

			Vector3 GetPosition() const;
			void SetPosition(const Vector3& position);

			Component* RegisterComponent(Component* component);
			void UnregisterComponent(Component* component);
			template <typename T>
			T* GetComponent()
			{
				for (auto component : m_RegisteredComponents)
				{
					if (auto tComp = dynamic_cast<T*>(component))
					{
						return tComp;
					}
				}
				return nullptr;
			}

		protected:
			virtual void OnPreInit() override;
			virtual void OnInit() override;
			virtual void OnPostInit() override;

			virtual void OnPreUpdate() override;
			virtual void OnUpdate(float dT) override;
			virtual void OnPostUpdate() override;

			virtual void OnDestroy() override;
	};
}
