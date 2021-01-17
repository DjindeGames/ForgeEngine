#pragma once

#include "engine/math/Math.h"
#include "engine/math/Transform.h"
#include "engine/core/ManagedObject.h"

#include <vector>

namespace ForgeEngine
{
	class Component;

	class Entity : public ManagedObject
	{
		using Mother = ManagedObject;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			Transform* m_Transform{};

			std::vector<Component*> m_RegisteredComponents;

			static std::vector<Entity*> s_RegisteredEntities;

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			static Entity* RegisterEntity();
			static void ReleaseEntities();

			Transform& GetTransform() const { return *m_Transform; }
			void SetTransform(const Transform& transform) const { *m_Transform = transform; }

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

			/* the following are to process the callback on all registered entities at once */
			static void PreInit();
			static void Init();
			static void PostInit();

			static void PreUpdate();
			static void Update(float dT);
			static void PostUpdate();

			static void DestroyEntity(ObjectID id);

			/* individual entities managed callbacks */
			virtual void OnPreInit() override;
			virtual void OnInit() override;
			virtual void OnPostInit() override;

			virtual void OnPreUpdate() override;
			virtual void OnUpdate(float dT) override;
			virtual void OnPostUpdate() override;

			void Destroy();

		protected:
			//Entities must be registered using RegisterEntity
			Entity();

			static Entity* RegisterEntity(Entity* entity);
			virtual void OnDestroy() override;
	};
}
