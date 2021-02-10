#pragma once

#include "engine/core/ManagedObjectContainer.h"
#include "engine/core/Manager.h"
#include "engine/core/Singleton.h"

namespace ForgeEngine
{
	class ManagerContainer : public ManagedObjectContainer, public Singleton<ManagerContainer>
	{
		using Mother = ManagedObjectContainer;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			void RegisterManager(Manager* manager)
			{
				Mother::RegisterObject(manager);
			}

			template <typename T>
			bool GetManager(T* manager)
			{
				manager = nullptr;
				for (auto& registeredManager : m_RegisteredObjects)
				{
					if (T* tManager = dynamic_cast<T*>(registeredManager.get()))
					{
						manager = tManager;
						return true;
					}
				}
				return false;
			}

			template <typename T>
			T* GetManagerByType()
			{
				for (auto& registeredManager : m_RegisteredObjects)
				{
					if (T* tManager = dynamic_cast<T*>(registeredManager.get()))
					{
						return tManager;
					}
				}
				return nullptr;
			}
	};
}