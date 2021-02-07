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

			Vector4 GetPosition() const { return m_Transform.GetPosition(); }
			void SetPosition(const Vector4& position) { m_Transform.SetPosition(position); }

			Component* RegisterComponent(Component* component);
			template <typename T>
			T* GetComponent()
			{
				for (auto component : m_RegisteredComponents)
				{
					if (auto tComp = dynamic_cast<T*>(component.get()))
					{
						return tComp.get();
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
