#pragma once

#include "system/math/Vector3.h"

namespace ForgeEngine
{
	namespace ForgeMaths
	{
		Vector3 ComputeCameraSight(float yaw, float pitch);
		
		template <typename T>
		T Clamp(T value, T minValue, T maxValue)
		{
			T retValue = value;
			if (retValue < minValue)
			{
				retValue = minValue;
			}
			else if (retValue > maxValue)
			{
				retValue = maxValue;
			}
			return retValue;
		}

		template <typename T>
		bool IsBetween(T value, T inf, T sup)
		{
			return (value >= inf && value <= sup);
		}

		template <typename T>
		bool IsBetweenExclusive(T value, T inf, T sup)
		{
			return (value > inf && value < sup);
		}
	}
}

