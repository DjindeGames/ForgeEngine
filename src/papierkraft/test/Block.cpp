#include "Block.h"

#include "engine/3d/MeshComponent.h"
#include "engine/common/ViewerComponent.h"
#include "engine/misc/Texture.h"

#include <vector>

using namespace ForgeEngine;

namespace PapierKraft
{
	Block::Block(Texture* sideTexture, Texture* topTexture, Texture* bottomTexture, Shader* shader) :
		Mother()
	{
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

		MeshComponent* sideMesh = new MeshComponent(sideVerticesTexturesCoordinates, sideCoordinates, shader);
		sideMesh->SetTexture(sideTexture);
		MeshComponent* topMesh = new MeshComponent(topVerticesTexturesCoordinates, topCoordinates, shader);
		topMesh->SetTexture(topTexture);
		MeshComponent* bottomMesh = new MeshComponent(bottomVerticesTexturesCoordinates, bottomCoordinates, shader);
		bottomMesh->SetTexture(bottomTexture);

		this->RegisterComponent(sideMesh);
		this->RegisterComponent(topMesh);
		this->RegisterComponent(bottomMesh);

		this->RegisterComponent(new ViewerComponent(360.f));
	}

	/*static*/ Block* Block::Create(Texture* sideTexture, Texture* topTexture, Texture* bottomTexture, Shader* shader)
	{
		Block* block = new Block(sideTexture, topTexture, bottomTexture, shader);
		return static_cast<Block*>(Mother::RegisterEntity(block));
	}

	/*static*/ Block* Block::Create(Texture* uniformTexture, Shader* shader)
	{
		return Create(uniformTexture, uniformTexture, uniformTexture, shader);
	}
}