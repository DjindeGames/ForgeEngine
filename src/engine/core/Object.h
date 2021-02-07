#pragma once

#include "engine/core/NonCopyable.h"

namespace ForgeEngine
{
	typedef unsigned long long int ObjectID;

	class Object : public NonCopyable
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			ObjectID m_ID{};

			static ObjectID s_LastGivenID;

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Object();
			virtual ~Object() {}

			ObjectID GetID() const { return m_ID; }
	};
}