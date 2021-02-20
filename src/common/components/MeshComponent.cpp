#include "MeshComponent.h"

#include "common/components/CameraComponent.h"
#include "engine/core/Entity.h"
#include "engine/core/ManagerContainer.h"
#include "engine/core/OpenGL.h"
#include "engine/misc/Texture.h"
#include "engine/shader/Shader.h"

#include <algorithm>
#include <iterator>
#include <utility>

namespace ForgeEngine
{
	MeshComponent::MeshComponent(
		const std::vector<float>& vertices,
		const std::vector<unsigned int>& indices,
		Shader* shader,
		const Color& renderColor /*= COLOR_RENDER_DEFAULT*/
	) :
		Mother(),
		m_renderColor(renderColor),
		m_Shader(shader)
	{
		InitRender(vertices, indices);
	}

	MeshComponent::MeshComponent(
		const std::vector<float>& vertices, 
		const std::vector<unsigned int>& indices, 
		Shader* shader, 
		Texture* texture
	) :
		Mother(),
		m_renderColor(COLOR_MAGENTA),
		m_Shader(shader),
		m_Texture(texture)
	{
		InitRender(vertices, indices);
	}

	void MeshComponent::InitRender(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
	{
		if (m_Shader == nullptr)
		{
			return;
		}

		m_NumIndices = static_cast<unsigned int>(indices.size());
		m_NumVertices = vertices.size() / m_Shader->GetInputDataSize();

		float* glFloats = new float[(vertices.size())];

		for (COUNTER i = 0; i < (vertices.size()); i++)
		{
			glFloats[i] = vertices[i];
		} 

		//Generates buffer to store vertices
		glGenBuffers(1, &m_VertexBufferObject);
		glGenVertexArrays(1, &m_VertexArrayObject);

		//Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

		//1. Bind Vertex Array Object
		glBindVertexArray(m_VertexArrayObject);

		//2. Copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), glFloats, GL_STATIC_DRAW);

		//2.5. Use vertex buffer element if necessary
		if (indices.size() > 0)
		{
			glGenBuffers(1, &m_VertexBufferElement);

			unsigned int* glIndices = new unsigned int[indices.size()];
			std::copy(indices.begin(), indices.end(), glIndices);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VertexBufferElement);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), glIndices, GL_STATIC_DRAW);

			delete[](glIndices);
		}

		//3. Then set our vertex attributes pointers
		//1st argument corresponds to the vertex attribute location (comes from vertexShaderSource)
		//2nd argument corresponds to the number of float in a vec3 (used in the vertex shader)
		//5th argument corresponds to the size of the stride in bytes, ie the number of bytes between 2 vec3
		//Should be done for each attribute of the vertexShader, eg each in variable
		int offset = 0;
		for (COUNTER i = 0; i < m_Shader->GetNBAttributes() ; i++)
		{
			unsigned int attributeSize = m_Shader->GetAttributeSize(i);
			glVertexAttribPointer(i, attributeSize, GL_FLOAT, GL_FALSE, m_Shader->GetInputDataSize() * sizeof(float), (void*)offset);
			offset += attributeSize * sizeof(float);
			//Argument corresponds to the vertex attribute location
			glEnableVertexAttribArray(i);
		}

		//Unbinding, this is optionnal

		//Note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		//VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);

		//Clear vertices data
		delete[](glFloats);
	}

	void MeshComponent::OnUpdate(float dT)
	{
		Mother::OnUpdate(dT);

		if (m_Shader != nullptr && CameraComponent::GetActiveCamera() != nullptr)
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			m_Shader->Use();
			m_Shader->SetColor(DEFAULT_RENDER_COLOR_NAME, m_renderColor);
			m_Shader->SetTexture(GL_TEXTURE0, m_Texture);
			m_Shader->SetFloat(DEFAULT_LIGHT_INTENSITY_NAME, 1.f);
			m_Shader->SetTransform(DEFAULT_TRANSFORM_NAME, &m_Owner->GetTransform());
			m_Shader->SetProjection(DEFAULT_PROJECTION_NAME, CameraComponent::GetActiveCamera()->GetProjection());
			m_Shader->SetView(DEFAULT_VIEW_NAME, CameraComponent::GetActiveCamera()->GetView());
			
			glBindVertexArray(m_VertexArrayObject);
			if (m_NumIndices > 0)
			{
				glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, 0);
			}
			else
			{
				glDrawArrays(GL_TRIANGLES, 0, m_NumVertices * m_Shader->GetInputDataSize());
			}
		}
	}

	void MeshComponent::OnDestroy() /*override*/
	{
		Mother::OnDestroy();
		glDeleteVertexArrays(1, &m_VertexArrayObject);
		glDeleteBuffers(1, &m_VertexBufferObject);
		glDeleteBuffers(1, &m_VertexBufferElement);
	}
}