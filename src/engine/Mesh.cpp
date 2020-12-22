#include "Mesh.h"

#include "math/Vector3.h"

#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ForgeEngine
{
	Mesh::Mesh(Vector3 vertices[], unsigned int numVertices, GL_ID shaderProgram) : 
		m_NumVertices(numVertices),
		m_ShaderProgram(shaderProgram)
	{
		const unsigned int glVerticesNumber = 3 * numVertices;
		float* m_Vertices = new float[glVerticesNumber];

		for (int i = 0; i < glVerticesNumber; i++)
		{
			//In opengl, all coordinate x, y, z are packed together into a single float array
			//thus we need to unpack our vector3 to store all x, y and z values in the same array
			m_Vertices[i] = vertices[i / 3][i % 3];
		}

		GL_ID vertexBufferObject{};

		//Generates buffer to store vertices
		glGenBuffers(1, &vertexBufferObject);
		glGenVertexArrays(1, &m_VertexArrayObject);

		//Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

		//1. Bind Vertex Array Object
		glBindVertexArray(m_VertexArrayObject);

		//2. Copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);

		//3. Then set our vertex attributes pointers
		//First argument corresponds to the vertex attribute location (comes from vertexShaderSource)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//Argument corresponds to the vertex attribute location
		glEnableVertexAttribArray(0);

		//Unbinding, this is optionnal

		//Note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		//VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);
	}

	Mesh::Mesh(float vertices[], unsigned int numVertices, GL_ID shaderProgram) :
		m_NumVertices(numVertices),
		m_ShaderProgram(shaderProgram)
	{
		GL_ID vertexBufferObject{};

		//Generates buffer to store vertices
		glGenBuffers(1, &vertexBufferObject);
		glGenVertexArrays(1, &m_VertexArrayObject);

		//Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

		//1. Bind Vertex Array Object
		glBindVertexArray(m_VertexArrayObject);

		//2. Copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//3. Then set our vertex attributes pointers
		//First argument corresponds to the vertex attribute location (comes from vertexShaderSource)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//Argument corresponds to the vertex attribute location
		glEnableVertexAttribArray(0);

		//Unbinding, this is optionnal

		//Note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		//VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);
	}

	Mesh::~Mesh()
	{
		delete[](m_Vertices);
	}

	void Mesh::Render()
	{
		glUseProgram(m_ShaderProgram);
		glBindVertexArray(m_VertexArrayObject);
		glDrawArrays(GL_TRIANGLES, 0, m_NumVertices);
	}
}