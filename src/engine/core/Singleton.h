#pragma once

#include "engine/core/NonCopyable.h"

#include <memory>

namespace ForgeEngine
{
	template <typename T>
	class Singleton : NonCopyable
	{
		/************************************/
		/**************METHODS***************/
		/************************************/
		
		public:
			//Not thread safe!
			static T* Get() 
			{
				static std::unique_ptr<T> m_Instance{ new T };
				return m_Instance.get();
			}

		protected:
			Singleton() {};
	};
}