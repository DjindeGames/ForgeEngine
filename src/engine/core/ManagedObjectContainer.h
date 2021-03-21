#pragma once

#include "engine/core/ManagedObject.h"
#include "engine/core/Object.h"

#include <memory>
#include <vector>

namespace ForgeEngine
{
	typedef unsigned long long int ObjectID;

	class GameHandler;
	class ManagedObject;

	class ManagedObjectContainer : Object
	{
		friend class GameHandler;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		protected:
			std::vector<std::unique_ptr<ManagedObject>> m_RegisteredObjects{};
			static const constexpr unsigned int K_MAX_INITIALIZATIONS_PER_FRAME = 1;

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

			void PreUpdate(float dT);
			void Update(float dT);
			void PostUpdate(float dT);

			void DrawDebug(float dT);

		private:
			void OnDestroy();
	};
}