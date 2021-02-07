#pragma once

#include "engine/core/Component.h"
#include "engine/math/Matrix4.h"

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

		private:
			void ClearActiveCameraIfNeeded();
	};
}