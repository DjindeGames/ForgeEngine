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
			template<typename T>
			void RegisterManager(Manager<T> manager)
			{
				Mother::RegisterObject(manager);
			}
			void ReleaseManagers();
	};
}