#include "Mesh.h"

#include "engine/misc/Texture.h"
#include "engine/shader/ShaderUtils.h"

#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iterator>
#include <utility>

namespace ForgeEngine
{
	Mesh::Mesh(
		const std::vector<float>& vertices,
		const std::vector<unsigned int>& indices,
		Shader* shader,
		const Color& renderColor /*= COLOR_RENDER_DEFAULT*/
	) :
		m_NumIndices(static_cast<unsigned int>(indices.size())),
		m_Floats(vertices),
		m_Indices(indices),
		m_renderColor(renderColor),
		m_Shader(shader)
	{
	}

	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &m_VertexArrayObject);
		glDeleteBuffers(1, &m_VertexBufferObject);
		glDeleteBuffers(1, &m_VertexBufferElement);
	}

	void Mesh::InitRender()
	{
		if (m_Shader == nullptr)
		{
			return;
		}

		m_NumVertices = m_Floats.size() / m_Shader->GetInputDataSize();

		float* glFloats = new float[(m_Floats.size())];

		for (COUNTER i = 0; i < (m_Floats.size()); i++)
		{
			glFloats[i] = m_Floats[i];
		} 

		//Generates buffer to store vertices
		glGenBuffers(1, &m_VertexBufferObject);
		glGenVertexArrays(1, &m_VertexArrayObject);

		//Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

		//1. Bind Vertex Array Object
		glBindVertexArray(m_VertexArrayObject);

		//2. Copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, m_Floats.size() * sizeof(float), glFloats, GL_STATIC_DRAW);

		//2.5. Use vertex buffer element if necessary
		if (m_Indices.size() > 0)
		{
			glGenBuffers(1, &m_VertexBufferElement);

			unsigned int* glIndices = new unsigned int[m_Indices.size()];
			std::copy(m_Indices.begin(), m_Indices.end(), glIndices);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VertexBufferElement);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), glIndices, GL_STATIC_DRAW);

			delete[](glIndices);
		}

		//3. Then set our vertex attributes pointers
		//1st argument corresponds to the vertex attribute location (comes from vertexShaderSource)
		//2nd argument corresponds to the number of float in a vec3 (used in the vertex shader)
		//5th argument corresponds to the size of the stride in bytes, ie the number of bytes between 2 vec3
		//Should be done for each attribute of the vertexShader, eg each in variable
		int offset = 0;
		for (auto attribute : m_Shader->GetAttributes())
		{
			glVertexAttribPointer(attribute.first, attribute.second, GL_FLOAT, GL_FALSE, m_Shader->GetInputDataSize() * sizeof(float), (void*)offset);
			offset += attribute.second * sizeof(float);
			//Argument corresponds to the vertex attribute location
			glEnableVertexAttribArray(attribute.first);
		}

		//Unbinding, this is optionnal

		//Note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		//VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);

		//Clear vertices data
		delete[](glFloats);
		m_Floats.erase(m_Floats.begin(), m_Floats.end());
		m_Indices.erase(m_Indices.begin(), m_Indices.end());

		m_IsInitialized = true;
	}

	void Mesh::Render()
	{
		if (!m_IsInitialized)
		{
			InitRender();
		}
		
		if (m_Shader != nullptr)
		{
			m_Shader->Use();
			m_Shader->SetColor(DEFAULT_RENDER_COLOR_NAME, m_renderColor);
			m_Shader->SetTexture(GL_TEXTURE0, m_Texture);
			
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
}