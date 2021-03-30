#pragma once

#include "engine/core/Component.h"
#include "engine/core/EntityContainer.h"
#include "engine/core/ManagedObject.h"

#include <memory>
#include <vector>

namespace ForgeEngine
{
	class Component;
	class TransformComponent;

	class Entity : public ManagedObject
	{
		using Mother = ManagedObject;

		friend Entity* EntityContainer::RegisterEntity();

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			mutable TransformComponent* m_Transform{};

			std::vector<std::unique_ptr<Component>> m_RegisteredComponents;

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			TransformComponent* GetTransform() const;

			template <typename T>
			T* RegisterComponent(T* component)
			{
				if (component != nullptr)
				{
					m_RegisteredComponents.push_back(std::unique_ptr<Component>(component));
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
