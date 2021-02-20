#pragma once

#include "engine/core/ManagerContainer.h"

namespace ForgeEngine
{
	namespace ManagerHelper
	{
		template <typename T>
		T* GetManagerByType()
		{
			if (ManagerContainer* managerContainer = ManagerContainer::Get())
			{
				return managerContainer->GetManagerByType<T>();
			}
			return nullptr;
		}
	}
}