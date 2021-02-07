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
			T* GetManagerByType()
			{
				for (auto& manager : m_RegisteredObjects)
				{
					if (auto ptr = dynamic_cast<T*>(manager.get()))
					{
						return ptr;
					}
				}
				return nullptr;
			}
	};
}