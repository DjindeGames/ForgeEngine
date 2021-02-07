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

			void SetActive(bool active) { m_IsActive = active; }
			bool IsActive() const { return m_IsActive; }

			virtual void OnPreInit() {}
			virtual void OnInit() {}
			virtual void OnPostInit() {}

			virtual void OnPreUpdate() {}
			virtual void OnUpdate(float dT) {}
			virtual void OnPostUpdate() {}

			void Destroy() { OnDestroy(); }
		
		protected:
			virtual void OnDestroy() {}
	};
}