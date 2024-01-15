#pragma once

#include "engine/core/Component.h"
#include "engine/core/Defines.h"
#include "engine/misc/Mesh.h"
#include "system/misc/Color.h"

#include <memory>
#include <string>

namespace ForgeEngine
{
	class Shader;
	class Texture;

	class MeshComponent : public Component
	{
		using Mother = Component;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
            Mesh m_Mesh{};
			std::shared_ptr<Shader> m_Shader{};

			GL_ID m_VertexArrayObject{};
			GL_ID m_VertexBufferObject{};
			GL_ID m_VertexBufferElement{};
			unsigned int m_NumIndices{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			MeshComponent(const Mesh& mesh, const std::string& shaderPath);

			virtual void OnUpdate(float dT) override;
			virtual void OnDestroy() override;

            Mesh& GetMesh() { return m_Mesh; }

		private:
			void InitRender();
	};
}