#pragma once

#include "engine/core/ManagedObjectContainer.h"
#include "engine/core/Object.h"

namespace ForgeEngine
{
	class ManagedObject : Object
	{
		using Mother = Object;

		friend class ManagedObjectContainer;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			bool m_IsActive{ true };

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			ManagedObject();

			void SetActive(bool active); 
			bool IsActive() const { return m_IsActive; }

			virtual void OnActivate() {}
			virtual void OnDeactivate() {}

			virtual bool OnPreInit() { return true; }
			virtual bool OnInit() { return true; }
			virtual bool OnPostInit() { return true; }

			virtual void OnPreUpdate(float dT) {}
			virtual void OnUpdate(float dT) {}
			virtual void OnPostUpdate(float dT) {}

			void Destroy() { OnDestroy(); }
		
		protected:
			virtual void OnDestroy() {}
	};
}