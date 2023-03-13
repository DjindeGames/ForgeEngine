#pragma once

#include "engine/core/Component.h"
#include "engine/core/Defines.h"
#include "engine/core/World.h"
#include "engine/core/ManagedObject.h"

#include <memory>
#include <vector>

namespace ForgeEngine
{
	class Component;
	class TransformComponent;
    class World;

	class Entity : public ManagedObject
	{
		using Mother = ManagedObject;

		friend class World;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
            World* m_World{ nullptr };
			mutable TransformComponent* m_Transform{ nullptr };

			std::vector<Unique<Component>> m_RegisteredComponents;

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			TransformComponent* GetTransform() const;
            World* GetWorld() { return m_World; }
            const World* GetWorld() const { return m_World; }

			template <typename T>
			T* RegisterComponent(T* component)
			{
				if (dynamic_cast<Component*>(component))
				{
					m_RegisteredComponents.push_back(Unique<Component>(component));
					component->SetOwner(this);
				}
				return component;
			}

			template <typename T>
			T* GetComponentByType() const
			{
				for (auto& registeredComponent : m_RegisteredComponents)
				{
					if (auto tComponent = dynamic_cast<T*>(registeredComponent.get()))
					{
						return tComponent;
					}
				}
				return nullptr;
			}

			template <typename T>
			bool GetComponent(T* component) const
			{
				component = nullptr;
				for (auto& registeredComponent : m_RegisteredComponents)
				{
					if (T* tComponent = dynamic_cast<T*>(registeredComponent.get()))
					{
						component = tComponent;
						return true;
					}
				}
				return false;
			}

		protected:
            Entity(World* world);

			virtual bool OnPreInit() override;
			virtual bool OnInit() override;
			virtual bool OnPostInit() override;

			virtual void OnPreUpdate(float dT) override;
			virtual void OnUpdate(float dT) override;
			virtual void OnPostUpdate(float dT) override;

			virtual void OnDrawDebug(float dT) override;

			virtual void OnDestroy() override;
	};
}
