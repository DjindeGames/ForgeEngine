#include "BlockComponent.h"

#include "common/components/ViewerComponent.h"
#include "engine/3d/MeshComponent.h"
#include "engine/misc/Texture.h"

#include <vector>

using namespace ForgeEngine;

namespace PapierKraft
{
	BlockComponent::BlockComponent(Texture* sideTexture, Texture* topTexture, Texture* bottomTexture, Shader* shader) :
		Mother(),
		m_SideTexture(sideTexture),
		m_TopTexture(topTexture),
		m_BottomTexture(bottomTexture),
		m_Shader(shader)
	{
	}

	BlockComponent::BlockComponent(Texture* sideTexture, Texture* restTexture, Shader* shader) :
		BlockComponent(sideTexture, restTexture, restTexture, shader)
	{
	}

	BlockComponent::BlockComponent(Texture* uniformTexture, Shader* shader) :
		BlockComponent(uniformTexture, uniformTexture, uniformTexture, shader)
	{
	}

	void BlockComponent::OnInit() /*override*/
	{
		Mother::OnInit();

		std::vector<float> sideVerticesTexturesCoordinates{
			/******************SIDE FRONT*******************/
				// positions       // texture coords
			 0.5f,  0.5f, 0.5f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.5f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.5f,   0.0f, 1.0f,  // top left 
			/******************SIDE RIGHT*******************/
				// positions       // texture coords
			 0.5f,  0.5f,-0.5f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f,-0.5f,   1.0f, 0.0f, // bottom right
			 0.5f, -0.5f, 0.5f,   0.0f, 0.0f, // bottom left
			 0.5f,  0.5f, 0.5f,   0.0f, 1.0f, // top left 
			 /******************SIDE BACK********************/
				// positions       // texture coords
			-0.5f,  0.5f,-0.5f,   1.0f, 1.0f, // top right
			-0.5f, -0.5f,-0.5f,   1.0f, 0.0f, // bottom right
			 0.5f, -0.5f,-0.5f,   0.0f, 0.0f, // bottom left
			 0.5f,  0.5f,-0.5f,   0.0f, 1.0f,  // top left 
			/******************SIDE LEFT********************/
				// positions       // texture coords
			-0.5f,  0.5f, 0.5f,   1.0f, 1.0f, // top right
			-0.5f, -0.5f, 0.5f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f,-0.5f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f,-0.5f,   0.0f, 1.0f // top left 
		};

		//Coordinate indexes 
		std::vector<unsigned int> sideCoordinates = {
			/******************SIDE FRONT*******************/
					0, 1, 3,
					1, 2, 3,
			/******************SIDE RIGHT*******************/
					4, 5, 7,
					5, 6, 7,
			/******************SIDE BACK********************/
					8, 9, 11,
					9, 10,11,
			/******************SIDE LEFT********************/
					12, 13, 15,
					13, 14, 15
		};

		std::vector<float> topVerticesTexturesCoordinates{
			/******************TOP**************************/
				// positions       // texture coords
			 0.5f, 0.5f, -0.5f,    1.0f, 1.0f, // top right
			 0.5f, 0.5f,  0.5f,    1.0f, 0.0f, // bottom right
			-0.5f, 0.5f,  0.5f,    0.0f, 0.0f, // bottom left
			-0.5f, 0.5f, -0.5f,    0.0f, 1.0f,  // top left 
		};

		//Coordinate indexes 
		std::vector<unsigned int> topCoordinates = {
			/******************TOP**************************/
					0, 1, 3,
					1, 2, 3
		};

		std::vector<float> bottomVerticesTexturesCoordinates{
			/******************BOTTOM***********************/
				// positions       // texture coords
			-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, // top right
			-0.5f, -0.5f,  0.5f,   1.0f, 0.0f, // bottom right
			 0.5f, -0.5f,  0.5f,   0.0f, 0.0f, // bottom left
			 0.5f, -0.5f, -0.5f,   0.0f, 1.0f  // top left
		};

		//Coordinate indexes 
		std::vector<unsigned int> bottomCoordinates = {
			/******************BOTTOM***********************/
					0, 1, 3,
					1, 2, 3
		};

		MeshComponent* sideMesh = new MeshComponent(sideVerticesTexturesCoordinates, sideCoordinates, m_Shader);
		sideMesh->SetTexture(m_SideTexture);
		MeshComponent* topMesh = new MeshComponent(topVerticesTexturesCoordinates, topCoordinates, m_Shader);
		topMesh->SetTexture(m_TopTexture);
		MeshComponent* bottomMesh = new MeshComponent(bottomVerticesTexturesCoordinates, bottomCoordinates, m_Shader);
		bottomMesh->SetTexture(m_BottomTexture);

		GetOwner()->RegisterComponent(sideMesh);
		GetOwner()->RegisterComponent(topMesh);
		GetOwner()->RegisterComponent(bottomMesh);

		GetOwner()->RegisterComponent(new ViewerComponent(1.f, 360.f, 1.01f));
	}
}