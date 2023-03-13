#pragma once

#include "engine/core/Defines.h"
#include "engine/core/Entity.h"
#include "engine/core/WorldComponent.h"

#include <memory>
#include <vector>

namespace ForgeEngine
{
    class Entity;
    class GameHandler;

	class World : ManagedObject
	{
		friend class GameHandler;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
            static const unsigned int K_MAX_INITIALIZATIONS_PER_FRAME = 1;

			std::vector<Unique<Entity>> m_RegisteredEntities{};
			std::vector<Unique<WorldComponent>> m_Components{};
			
		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			~World();

            Entity* RegisterEntity();

            template <typename T>
            T* RegisterComponent(T* component)
            {
                if (dynamic_cast<WorldComponent*>(component))
                {
                    m_Components.push_back(Unique<WorldComponent>(component));
                    component->SetWorld(this);
                }
                return component;
            }

            template <typename T>
            T* GetComponentByType() const
            {
                for (auto& registeredComponent : m_Components)
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
                for (auto& registeredComponent : m_Components)
                {
                    if (T * tComponent = dynamic_cast<T*>(registeredComponent.get()))
                    {
                        component = tComponent;
                        return true;
                    }
                }
                return false;
            }

		private:
            bool PreInit();
            bool Init();
            bool PostInit();

            void PreUpdate(float dT);
            void Update(float dT);
            void PostUpdate(float dT);

            void DrawDebug(float dT);

			void OnDestroy();
	};
}