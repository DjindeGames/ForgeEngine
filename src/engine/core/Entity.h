#pragma once

#include "engine/math/Math.h"
#include "engine/math/Transform.h"

#include <vector>

namespace ForgeEngine
{
	class Mesh;

	class Entity
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		public:
			Transform* m_Transform{};

		private:
			Mesh* m_Mesh{};
			Vector3 m_Position;

			static std::vector<Entity*> s_Entities;

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Entity();
			~Entity();

			static Entity* RegisterEntity();
			static void Update(float dT);
			static void ReleaseEntities();

			void SetMesh(Mesh* mesh) { m_Mesh = mesh; }

			const Vector3& GetPosition() const { return m_Position; }
			void SetPosition(const Vector3& position) { m_Position = position; }

		private:
			void UpdateInternal(float dT);
	};
}
