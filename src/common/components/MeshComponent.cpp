#include "MeshComponent.h"

#include "common/components/CameraComponent.h"
#include "engine/core/ForgeEngine.h"
#include "engine/misc/Texture.h"
#include "engine/shader/Shader.h"
#include "common/components/LightComponent.h"
#include "common/worldcomponents/LightManager.h"

#include <algorithm>
#include <iterator>
#include <utility>

namespace ForgeEngine
{
	MeshComponent::MeshComponent(const Mesh& mesh, Shader* shader) 
        : Mother()
        , m_Mesh(mesh)
        , m_Shader(shader)
	{
		InitRender();
	}

	void MeshComponent::InitRender()
	{
        if (m_Shader == nullptr)
        {
            //TODO: Add error message
            return;
        }

        std::vector<float> meshData = m_Mesh.MakeGLData();

		//Generates buffer to store vertices
		glGenBuffers(1, &m_VertexBufferObject);
		glGenVertexArrays(1, &m_VertexArrayObject);

		//Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

		//1. Bind Vertex Array Object
		glBindVertexArray(m_VertexArrayObject);

		//2. Copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
        const GLintptr meshDataSize = meshData.size() * sizeof(float);
		glBufferData(GL_ARRAY_BUFFER, meshDataSize, meshData.data(), GL_STATIC_DRAW);

		//2.5. Use vertex buffer element
		glGenBuffers(1, &m_VertexBufferElement);
        std::vector<unsigned int> indices = m_Mesh.GetTrianglesIndices();
        m_NumIndices = indices.size();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VertexBufferElement);
        const GLintptr indicesSize = indices.size() * sizeof(unsigned int);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices.data(), GL_STATIC_DRAW);

		//3. Then set our vertex attributes pointers
		//1st argument corresponds to the vertex attribute location (comes from vertexShaderSource)
		//2nd argument corresponds to the number of floats in the attribute (used in the vertex shader)
		//5th argument corresponds to the size of the attribute in bytes
		//Should be done for each attribute of the vertexShader, eg each in variable
		int offset = 0;
        const unsigned int inputDataSize = m_Shader->GetInputDataSize() * sizeof(float);
		for (COUNTER i = 0; i < m_Shader->GetNBAttributes() ; i++)
		{
			unsigned int attributeSize = m_Shader->GetAttributeSize(i);
			glVertexAttribPointer(i, attributeSize, GL_FLOAT, GL_FALSE, inputDataSize, (void*)offset);
			glEnableVertexAttribArray(i);
			offset += attributeSize * sizeof(float);
		}

		//Unbinding, this is optionnal

		//Note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		//VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);
	}

	void MeshComponent::OnUpdate(float dT)
	{
		Mother::OnUpdate(dT);

		if (m_Shader != nullptr)
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			m_Shader->Use();
			m_Shader->SetColor(DEFAULT_RENDER_COLOR_NAME, m_Mesh.GetRenderColor());
			m_Shader->SetTexture(GL_TEXTURE0, m_Mesh.GetTexture());
			m_Shader->SetTransform(DEFAULT_TRANSFORM_NAME, m_Owner->GetTransform());

            //Lighting
            std::vector<const LightComponent*> lights = GameHandler::Get().GetWorld().GetComponentByType<LightManager>()->GetLightsInRange(GetOwner()->GetPosition());
            if (!lights.empty())
            {
                m_Shader->SetColor(DEFAULT_LIGHT_COLOR_NAME, lights[0]->GetColor());
                m_Shader->SetVector4(DEFAULT_LIGHT_SOURCE_POSITION_NAME, lights[0]->GetOwner()->GetPosition());
                m_Shader->SetFloat(DEFAULT_LIGHT_INTENSITY_NAME, lights[0]->GetIntensity());
            }

			if (CameraComponent::GetActiveCamera() != nullptr)
			{
				m_Shader->SetProjection(DEFAULT_PROJECTION_NAME, CameraComponent::GetActiveCamera()->GetProjection());
				m_Shader->SetView(DEFAULT_VIEW_NAME, CameraComponent::GetActiveCamera()->GetView());
			}

			glBindVertexArray(m_VertexArrayObject);
			glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, 0);
		}
	}

	void MeshComponent::OnDestroy() /*override*/
	{
		glDeleteVertexArrays(1, &m_VertexArrayObject);
		glDeleteBuffers(1, &m_VertexBufferObject);
		glDeleteBuffers(1, &m_VertexBufferElement);
		Mother::OnDestroy();
	}
}