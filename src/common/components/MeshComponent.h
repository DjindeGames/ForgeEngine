#pragma once

#include "engine/core/Component.h"
#include "engine/core/CoreEngine.h"
#include "engine/misc/Color.h"

#include <vector>

namespace ForgeEngine
{
	class Shader;
	class Texture;

	//A mesh is built using a collection of Vector3 that represents its vertices
	//Those vertices are converted into an array of floats to match openGL behaviour
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

			std::vector<unsigned int> m_Indices{};
			std::vector<float> m_Floats{};
			unsigned int m_NumVertices{};
			unsigned int m_NumIndices{};

			bool m_IsInitialized{ false };

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			MeshComponent(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, Shader* shader, const Color& renderColor = COLOR_MAGENTA);
			MeshComponent(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, Shader* shader, Texture* texture);

			void SetTexture(Texture* texture) { m_Texture = texture; }

			virtual void OnUpdate(float dT) override;
			virtual void OnDestroy() override;

		private:
			//CHANGE FOR ONINIT
			void InitRender();
	};
}