#pragma once

#include "engine/math/Transform.h"
#include "engine/Core/Component.h"
#include "engine/core/EntityContainer.h"
#include "engine/core/ManagedObject.h"

#include <memory>
#include <vector>

namespace ForgeEngine
{
	class Component;
	class Transform;

	class Entity : public ManagedObject
	{
		using Mother = ManagedObject;

		friend Entity* EntityContainer::RegisterEntity();

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			Transform m_Transform{};

			std::vector<std::unique_ptr<Component>> m_RegisteredComponents;

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Transform& GetTransform() { return m_Transform; }
			void SetTransform(const Transform& transform) { m_Transform = transform; }

			Vector3 GetPosition() const { return m_Transform.GetPosition(); }
			void SetPosition(const Vector3& position) { m_Transform.SetPosition(position); }

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
			T* GetComponentByType()
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
			bool GetComponent(T* component)
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

			virtual void OnPreUpdate() override;
			virtual void OnUpdate(float dT) override;
			virtual void OnPostUpdate() override;

			virtual void OnDestroy() override;
	};
}
