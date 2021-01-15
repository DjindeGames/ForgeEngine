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

		public:
			Transform* m_Transform{};

		private:
			Vector3 m_Position;
			std::vector<Component*> m_RegisteredComponents;

			static std::vector<Entity*> s_RegisteredEntities;

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			static Entity* RegisterEntity();
			static void ReleaseEntities();

			void RegisterComponent(Component* component);
			void UnregisterComponent(Component* component);
			template <typename T>
			T* GetComponent();

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

			const Vector3& GetPosition() const { return m_Position; }
			void SetPosition(const Vector3& position) { m_Position = position; }

		protected:
			virtual void OnDestroy() override;

		private:
			//Entities must be registered using RegisterEntity
			Entity();
	};
}
