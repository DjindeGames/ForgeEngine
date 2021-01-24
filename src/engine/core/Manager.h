#pragma once

#include "engine/core/ManagedObject.h"
#include "engine/core/Singleton.h"

namespace ForgeEngine
{
	template<typename T>
	class Manager : public ManagedObject, public Singleton<T>
	{
		using Mother = ManagedObject;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		/************************************/
		/**************METHODS***************/
		/************************************/
	};
}