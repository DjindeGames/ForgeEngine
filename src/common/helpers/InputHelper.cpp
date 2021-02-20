#include "InputHelper.h"

#include "common/helpers/ManagerHelper.h"
#include "common/managers/InputManager.h"

namespace ForgeEngine
{
	namespace InputHelper
	{
		bool IsInputActive(EInputAction type)
		{
			if (InputManager * inputManager = ManagerHelper::GetManagerByType<InputManager>())
			{
				return inputManager->IsInputActive(type);
			}
			return false;
		}

		Vector2 GetMouseVelocity()
		{
			if (InputManager * inputManager = ManagerHelper::GetManagerByType<InputManager>())
			{
				return inputManager->GetMouseVelocity();
			}
			return VECTOR2_NULL;
		}

		Vector2 GetMousePosition()
		{
			if (InputManager * inputManager = ManagerHelper::GetManagerByType<InputManager>())
			{
				return inputManager->GetMousePosition();
			}
			return VECTOR2_NULL;
		}
	}
}