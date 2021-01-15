#pragma once

namespace ForgeEngine
{
	typedef unsigned long long int ObjectID;

	class ManagedObject
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
			ManagedObject();
			~ManagedObject() {}

			ObjectID GetID() const { return m_ID; }

			virtual void OnPreInit() {};
			virtual void OnInit() {};
			virtual void OnPostInit() {};

			virtual void OnPreUpdate() {};
			virtual void OnUpdate(float dT) {};
			virtual void OnPostUpdate() {};

		protected:
			virtual void OnDestroy() {};
	};
}