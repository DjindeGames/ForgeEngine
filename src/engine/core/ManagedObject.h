#pragma once

#include "engine/core/ManagedObjectContainer.h"

namespace ForgeEngine
{
	typedef unsigned long long int ObjectID;

	class ManagedObject
	{
		friend class ManagedObjectContainer;

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
			ObjectID GetID() const { return m_ID; }
		protected:
			ManagedObject();
			~ManagedObject() {}

			virtual void OnPreInit() {}
			virtual void OnInit() {}
			virtual void OnPostInit() {}

			virtual void OnPreUpdate() {}
			virtual void OnUpdate(float dT) {}
			virtual void OnPostUpdate() {}

			virtual void OnDestroy() {}

			void Destroy() { OnDestroy(); }
			
	};
}