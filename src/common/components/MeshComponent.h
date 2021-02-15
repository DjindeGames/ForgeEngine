#pragma once

#include "engine/core/Component.h"
#include "engine/core/Defines.h"
#include "system/misc/Color.h"

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
			Shader* m_Shader{};
			Texture* m_Texture{};
			Color m_renderColor;

			GL_ID m_VertexArrayObject{};
			GL_ID m_VertexBufferObject{};
			GL_ID m_VertexBufferElement{};

			unsigned int m_NumVertices{};
			unsigned int m_NumIndices{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			MeshComponent(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, Shader* shader, const Color& renderColor = COLOR_MAGENTA);
			MeshComponent(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, Shader* shader, Texture* texture);

			virtual void OnUpdate(float dT) override;
			virtual void OnDestroy() override;

		private:
			void InitRender(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
	};
}