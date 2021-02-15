#pragma once

#include "engine/core/Component.h"
#include "system/math/Matrix4.h"

namespace ForgeEngine
{
	class CameraComponent : public Component
	{
		using Mother = Component;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		public:
			static const CameraComponent* s_ActiveCamera;

		private:
			Matrix4 m_View{};
			Matrix4 m_Projection{};

			const Entity* m_FocusedEntity{};
			bool m_IsFocusActive{false};

			float m_Yaw{-90.f};
			float m_Pitch{0.f};
			Vector3 m_Sight{};
			Vector3 m_Right{};
			Vector3 m_Up{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			CameraComponent(float fov = 45.f, float aspectRatio = 16.f / 9.f, float nearPlane = 0.1f, float farPlane = 100.f);

			static const CameraComponent* GetActiveCamera() { return s_ActiveCamera; }
			const Matrix4& GetProjection() const { return m_Projection; }
			const Matrix4& GetView() const { return m_View; }

			virtual void OnUpdate(float dT) override;
			virtual void OnActivate() override;
			virtual void OnDeactivate() override;
			virtual void OnDestroy() override;

			void SetFocusedEntity(const Entity* entity) { m_FocusedEntity = entity; }
			void SetFocusActive(bool active) { m_IsFocusActive = active; }
			float GetYaw() const        { return m_Yaw; }
			void  SetYaw(float yaw)     { m_Yaw = yaw; }
			float GetPitch() const      { return m_Pitch; }
			void  SetPitch(float pitch) { m_Pitch = pitch; }

			Vector3 GetSight()	const { return m_Sight; }
			Vector3 GetRight()	const { return m_Right; }
			Vector3 GetUp()		const { return m_Up; }

		private:
			void ClearActiveCameraIfNeeded();
			void RefreshView();
	};
}