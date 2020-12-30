#include "Mesh.h"

#include "engine/math/Vector3.h"
#include "engine/shader/ShaderUtils.h"

#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iterator>

namespace ForgeEngine
{

	Mesh::Mesh(
		const std::vector<Vector3>& vertices,  
		const std::vector<unsigned int>& indices /*= std::vector<unsigned int>{}*/,
		Color renderColor /*= COLOR_MAGENTA*/

	) :
		m_ShaderProgram(ShaderUtils::GetDefaultShaderProgram()),
		m_NumVertices(static_cast<unsigned int>(vertices.size())),
		m_NumIndices(static_cast<unsigned int>(indices.size())),
		m_Vertices(vertices),
		m_Indices(indices),
		m_renderColor(renderColor)
	{
	}

	Mesh::Mesh(
		const std::vector<Vector3>& vertices,
		Color renderColor /*= COLOR_MAGENTA*/
	) :
		m_ShaderProgram(ShaderUtils::GetDefaultShaderProgram()),
		m_NumVertices(static_cast<unsigned int>(vertices.size())),
		m_NumIndices(static_cast<unsigned int>(0)),
		m_Vertices(vertices),
		m_renderColor(renderColor)
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
		float* glVertices = new float[(m_NumVertices * 3)];

		for (COUNTER i = 0; i < (m_NumVertices * 3); i++)
		{
			//In opengl, all coordinate x, y, z are packed together into a single float array
			//thus we need to unpack our vector3 to store all x, y and z values in the same array
			glVertices[i] = m_Vertices[i / 3][i % 3];
		} 

		//Generates buffer to store vertices
		glGenBuffers(1, &m_VertexBufferObject);
		glGenVertexArrays(1, &m_VertexArrayObject);

		//Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

		//1. Bind Vertex Array Object
		glBindVertexArray(m_VertexArrayObject);

		//2. Copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, m_NumVertices * sizeof(float) * 3, glVertices, GL_STATIC_DRAW);

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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//Argument corresponds to the vertex attribute location
		glEnableVertexAttribArray(0);

		//Unbinding, this is optionnal

		//Note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		//VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);

		delete[](glVertices);
	}

	void Mesh::Render()
	{
		if (!m_IsInitialized)
		{
			m_IsInitialized = true;
			InitRender();
		}

		//Set rendering color
		int vertexColorLocation = glGetUniformLocation(m_ShaderProgram, "renderColor");
		glUseProgram(m_ShaderProgram);
		glUniform4f(vertexColorLocation, m_renderColor.GetR(), m_renderColor.GetG(), m_renderColor.GetB(), m_renderColor.GetA());

		glBindVertexArray(m_VertexArrayObject);
		if (m_NumIndices > 0)
		{
			glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, m_NumVertices * 3);
		}
	}
}