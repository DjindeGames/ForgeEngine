#include "BlockComponent.h"

#include "papierkraft/test/BlockTextureData.h"
#include "papierkraft/test/BlockTextureManager.h"

#include "common/components/ViewerComponent.h"
#include "common/managers/ShaderManager.h"
#include "common/components/MeshComponent.h"
#include "engine/core/ManagerContainer.h"
#include "engine/misc/Texture.h"

#include <vector>

using namespace ForgeEngine;

namespace PapierKraft
{
	BlockComponent::BlockComponent(EBlockType blockType) :
		Mother(),
		m_BlockType(blockType),
		m_TextureData(ManagerContainer::Get()->GetManagerByType<BlockTextureManager>()->GetTextureDataByBlockType(blockType)),
		m_Shader(ManagerContainer::Get()->GetManagerByType<ShaderManager>()->GetShaderByType(EShaderType::Textured))
	{
	}

	bool BlockComponent::OnPreInit() /*override*/
	{
		bool success = Mother::OnPreInit();

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

		GetOwner()->RegisterComponent(new MeshComponent(sideVerticesTexturesCoordinates, sideCoordinates, m_Shader, m_TextureData->GetSideTexture()));
		GetOwner()->RegisterComponent(new MeshComponent(topVerticesTexturesCoordinates, topCoordinates, m_Shader, m_TextureData->GetTopTexture()));
		GetOwner()->RegisterComponent(new MeshComponent(bottomVerticesTexturesCoordinates, bottomCoordinates, m_Shader, m_TextureData->GetBottomTexture()));
		return success;
	}
}