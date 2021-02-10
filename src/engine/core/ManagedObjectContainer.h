#pragma once

#include "engine/core/ManagedObject.h"
#include "engine/core/Object.h"

#include <memory>
#include <vector>

namespace ForgeEngine
{
	typedef unsigned long long int ObjectID;

	class Game;
	class ManagedObject;

	class ManagedObjectContainer : Object
	{
		friend class Game;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		protected:
			std::vector<std::unique_ptr<ManagedObject>> m_RegisteredObjects{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			~ManagedObjectContainer();

		protected:
			ManagedObject* RegisterObject(ManagedObject* object);

			bool PreInit();
			bool Init();
			bool PostInit();

			void PreUpdate();
			void Update(float dT);
			void PostUpdate();

		private:
			void OnDestroy();
	};
}