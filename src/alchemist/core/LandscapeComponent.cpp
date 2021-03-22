#include "LandscapeComponent.h"

#include "engine/core/GameHandler.h"
#include "engine/core/OpenGL.h"
#include "engine/ui/ImGUI.h"
#include "engine/misc/Texture.h"
#include "common/helpers/InputHelper.h"
#include "common/helpers/ManagerHelper.h"
#include "common/components/MeshComponent.h"
#include "common/managers/ShaderManager.h"
#include "system/math/MathUtils.h"

#include <vector>

namespace Alchemist
{
	bool LandscapeComponent::OnPreInit() /*override*/
	{
		std::vector<float> vertices
		{
			8.f, 4.5f, 0.f, 1.f, 1.f, // top right
			8.f, -4.5f, 0.f, 1.f, 0.f, // bottom right
			-8.f, -4.5f, 0.f, 0.f, 0.f, // bottom left
			-8.f, 4.5f, 0.f, 0.f, 1.f  // top left 
		};

		std::vector<unsigned int> indices
		{
			0, 1, 3,
			1, 2, 3
		};

		GetOwner()->RegisterComponent(new MeshComponent(vertices, indices, ManagerHelper::GetManagerByType<ShaderManager>()->GetShaderByType(EShaderType::Textured)));

		return true;
	}

	void LandscapeComponent::OnPreUpdate(float dT) /*override*/
	{
		Mother::OnPreUpdate(dT);

		Vector2 mousePosition = GetMousePosition();
		unsigned int pixelX = mousePosition.x;
		unsigned int pixelY = ALCHEMIST_LANDSCAPE_HEIGHT - mousePosition.y;

		if (ForgeMaths::IsBetween(pixelY, 0, ALCHEMIST_LANDSCAPE_HEIGHT - 1) && 
			ForgeMaths::IsBetween(pixelX, 0, ALCHEMIST_LANDSCAPE_WIDTH - 1) &&
			m_ParticleContainer[pixelY][pixelX].m_Type == EParticleType::Air)
		{
			if (InputHelper::IsInputActive(EInputAction::LeftClick))
			{
				SpawnParticle(EParticleType::Sand, pixelX, pixelY);
			}
			else if (InputHelper::IsInputActive(EInputAction::RightClick))
			{
				SpawnParticle(EParticleType::Water, pixelX, pixelY);
			}
		}

		UpdateParticles();

		DrawTexture();

		if (MeshComponent* mesh = GetOwner()->GetComponentByType<MeshComponent>())
		{
			mesh->SetTexture(m_Texture.get());
		}
	}

	void LandscapeComponent::OnDrawDebug(float dT) /*override*/ 
	{
		Vector2 mousePosition = GetMousePosition();

		ImGui::Begin("Alchemist");
		ImGui::Text("Grid Mouse Position {%f,%f}", mousePosition.x, mousePosition.y);
		ImGui::End();
	}

	Vector2 LandscapeComponent::GetMousePosition() const
	{
		float heightConversionRatio = GameHandler::m_WindowHeight / ALCHEMIST_LANDSCAPE_HEIGHT;
		float widthConversionRatio = GameHandler::m_WindowWidth / ALCHEMIST_LANDSCAPE_WIDTH;
		Vector2 mousePosition = InputHelper::GetMousePosition();
		return Vector2{ mousePosition.x / widthConversionRatio, mousePosition.y / heightConversionRatio };
	}

	void LandscapeComponent::UpdateParticles()
	{
		for (unsigned short x = 0; x < ALCHEMIST_LANDSCAPE_WIDTH; x++)
		{
			for (unsigned short y = 0; y < ALCHEMIST_LANDSCAPE_HEIGHT; y++)
			{
				if (!m_ParticleContainer[y][x].m_HasBeenUpdated)
				{
					m_ParticleContainer[y][x].m_HasBeenUpdated = true;
					EParticleType particleBeneath = GetSurroundingParticleType(EDirection::Bottom, x, y);
					switch (m_ParticleContainer[y][x].m_Type)
					{
						case(EParticleType::Sand):
							UpdateSand(x, y);
							break;
						case(EParticleType::Water):
							UpdateWater(x, y);
							break;
					}
				}
			}
		}

		for (unsigned short x = 0; x < ALCHEMIST_LANDSCAPE_WIDTH; x++)
		{
			for (unsigned short y = 0; y < ALCHEMIST_LANDSCAPE_HEIGHT; y++)
			{
				m_ParticleContainer[y][x].m_HasBeenUpdated = false;
			}
		}
	}

	void LandscapeComponent::SpawnParticle(EParticleType type, int x, int y)
	{
		switch (type)
		{
			case(EParticleType::Sand):
				m_ParticleContainer[y][x] = PARTICLE_SAND;
				break;
			case(EParticleType::Water):
				m_ParticleContainer[y][x] = PARTICLE_WATER;
				break;
		}
	}

	EParticleType LandscapeComponent::GetSurroundingParticleType(EDirection direction, unsigned int centerX, unsigned int centerY) const
	{
		EParticleType type = EParticleType::Border;
		switch (direction)
		{
			case(EDirection::TopLeft):
				if (centerX > 0 && centerY < ALCHEMIST_LANDSCAPE_HEIGHT - 1)
				{
					type = m_ParticleContainer[centerY + 1][centerX - 1].m_Type;
				}
				break;
			case(EDirection::Top):
				if (centerY < ALCHEMIST_LANDSCAPE_HEIGHT - 1)
				{
					type = m_ParticleContainer[centerY + 1][centerX].m_Type;
				}
				break;
			case(EDirection::TopRight):
				if (centerX < ALCHEMIST_LANDSCAPE_WIDTH - 1 && centerY < ALCHEMIST_LANDSCAPE_HEIGHT - 1)
				{
					type = m_ParticleContainer[centerY + 1][centerX - 1].m_Type;
				}
				break;
			case(EDirection::Left):
				if (centerX > 0)
				{
					type = m_ParticleContainer[centerY][centerX - 1].m_Type;
				}
				break;
			case(EDirection::Right):
				if (centerX < ALCHEMIST_LANDSCAPE_WIDTH - 1)
				{
					type = m_ParticleContainer[centerY][centerX + 1].m_Type;
				}
				break;
			case(EDirection::BottomLeft):
				if (centerX > 0 && centerY > 0)
				{
					type = m_ParticleContainer[centerY - 1][centerX - 1].m_Type;
				}
				break;
			case(EDirection::Bottom):
				if (centerY > 0)
				{
					type = m_ParticleContainer[centerY - 1][centerX].m_Type;
				}
				break;
			case(EDirection::BottomRight):
				if (centerX < ALCHEMIST_LANDSCAPE_WIDTH - 1 && centerY > 0)
				{
					type = m_ParticleContainer[centerY - 1][centerX + 1].m_Type;
				}
				break;
		}

		return type;
	}

	void LandscapeComponent::DrawTexture()
	{
		m_Texture.release();
		GeneratePixels();
		m_Texture = std::make_unique<Texture>(m_Pixels, ALCHEMIST_LANDSCAPE_WIDTH, ALCHEMIST_LANDSCAPE_HEIGHT);
	}
	
	void LandscapeComponent::GeneratePixels()
	{
		for (unsigned short x = 0; x < ALCHEMIST_LANDSCAPE_WIDTH; x++)
		{
			for (unsigned short y = 0; y < ALCHEMIST_LANDSCAPE_HEIGHT; y++)
			{
				Color particleColor = GetColorForParticleType(m_ParticleContainer[y][x].m_Type);
				unsigned int basePixelIndex = ((y * ALCHEMIST_LANDSCAPE_WIDTH) + x) * ALCHEMIST_PIXEL_DATA_SIZE;
				m_Pixels[basePixelIndex] = particleColor.GetRRatio();
				m_Pixels[basePixelIndex + 1] = particleColor.GetGRatio();
				m_Pixels[basePixelIndex + 2] = particleColor.GetBRatio();
			}
		}
	}

	Color LandscapeComponent::GetColorForParticleType(EParticleType type) const
	{
		Color color = COLOR_MAGENTA;
		switch (type)
		{
			case(EParticleType::Air):
				color = COLOR_BLACK;
				break;
			case(EParticleType::Water):
				color = COLOR_BLUE;
				break;
			case(EParticleType::Sand):
				color = COLOR_YELLOW;
				break;
		}
		return color;
	}

	void LandscapeComponent::UpdateSand(unsigned int x, unsigned int y)
	{
		Particle currentParticle = m_ParticleContainer[y][x];
		if (GetSurroundingParticleType(EDirection::Bottom, x, y) != EParticleType::Border && 
			GetSurroundingParticleType(EDirection::Bottom, x, y) != EParticleType::Sand)
		{
			m_ParticleContainer[y][x] = PARTICLE_AIR;
			m_ParticleContainer[y - 1][x] = currentParticle;
		}
		else if (GetSurroundingParticleType(EDirection::BottomLeft, x, y) != EParticleType::Border 
			&& GetSurroundingParticleType(EDirection::BottomLeft, x, y) != EParticleType::Sand)
		{
			m_ParticleContainer[y][x] = PARTICLE_AIR;
			m_ParticleContainer[y - 1][x - 1] = currentParticle;
		}
		else if (GetSurroundingParticleType(EDirection::BottomRight, x, y) != EParticleType::Border 
			&& GetSurroundingParticleType(EDirection::BottomRight, x, y) != EParticleType::Sand)
		{
			m_ParticleContainer[y][x] = PARTICLE_AIR;
			m_ParticleContainer[y - 1][x + 1] = currentParticle;
		}
	}

	void LandscapeComponent::UpdateWater(unsigned int x, unsigned int y)
	{
		Particle currentParticle = m_ParticleContainer[y][x];
		if (GetSurroundingParticleType(EDirection::Bottom, x, y) == EParticleType::Air)
		{
			m_ParticleContainer[y][x] = m_ParticleContainer[y - 1][x];
			m_ParticleContainer[y - 1][x] = currentParticle;
		}
		else if (GetSurroundingParticleType(EDirection::BottomLeft, x, y) == EParticleType::Air)
		{
			m_ParticleContainer[y][x] = m_ParticleContainer[y - 1][x - 1];
			m_ParticleContainer[y - 1][x - 1] = currentParticle;
		}
		else if (GetSurroundingParticleType(EDirection::BottomRight, x, y) == EParticleType::Air)
		{
			m_ParticleContainer[y][x] = m_ParticleContainer[y - 1][x + 1];
			m_ParticleContainer[y - 1][x + 1] = currentParticle;
		}
		else if (GetSurroundingParticleType(EDirection::Left, x, y) == EParticleType::Air)
		{
			m_ParticleContainer[y][x] = m_ParticleContainer[y][x - 1];
			m_ParticleContainer[y][x - 1] = currentParticle;
			
		}
		else if (GetSurroundingParticleType(EDirection::Right, x, y) == EParticleType::Air)
		{
			m_ParticleContainer[y][x] = m_ParticleContainer[y][x + 1];
			m_ParticleContainer[y][x + 1] = currentParticle;
		}
	}
}