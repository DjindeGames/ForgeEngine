#pragma once

#include <vector>

namespace ForgeEngine
{
	typedef unsigned long long int ObjectID;

	class Game;
	class ManagedObject;

	class ManagedObjectContainer
	{
		friend class Game;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			std::vector<ManagedObject*> s_RegisteredObjects;

		/************************************/
		/**************METHODS***************/
		/************************************/
		public:
			ManagedObjectContainer() {};
			ManagedObjectContainer(const ManagedObjectContainer&) = default;

		protected:
			ManagedObject* RegisterObject(ManagedObject*);
			void DestroyObject(ObjectID id);
			void ReleaseObjects();

			void PreInit();
			void Init();
			void PostInit();

			void PreUpdate();
			void Update(float dT);
			void PostUpdate();
	};
}