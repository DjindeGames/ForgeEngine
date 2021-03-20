#include "LandscapeComponent.h"

#include "engine/core/OpenGL.h"
#include "engine/misc/Texture.h"
#include "common/helpers/ManagerHelper.h"
#include "common/components/MeshComponent.h"
#include "common/managers/ShaderManager.h"

#include <vector>

namespace Alchemist
{
	bool LandscapeComponent::OnPreInit() /*override*/
	{
		std::vector<float> vertices
		{
			1.f, 1.f, -1.f, 1.f, 1.f, // top right
			1.f, -1.f, -1.f, 1.f, 0.f, // bottom right
			-1.f, -1.f, -1.f, 0.f, 0.f, // bottom left
			-1.f, 1.f, -1.f, 0.f, 1.f  // top left 
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

		static unsigned int particles = 0;

		if (particles < 1000)
		{
			particles++;
			m_ParticleContainer[ALCHEMIST_LANDSCAPE_HEIGHT - 1][ALCHEMIST_LANDSCAPE_WIDTH / 2] = PARTICLE_SAND;
			m_ParticleContainer[ALCHEMIST_LANDSCAPE_HEIGHT - 1][ALCHEMIST_LANDSCAPE_WIDTH / 3] = PARTICLE_WATER;
		}
		
		UpdateParticles();

		DrawTexture();

		if (MeshComponent* mesh = GetOwner()->GetComponentByType<MeshComponent>())
		{
			mesh->SetTexture(m_Texture.get());
		}
	}

	void LandscapeComponent::UpdateParticles()
	{
		for (unsigned short x = 0; x < ALCHEMIST_LANDSCAPE_WIDTH; x++)
		{
			for (unsigned short y = 0; y < ALCHEMIST_LANDSCAPE_HEIGHT; y++)
			{
				if (!m_ParticleContainer[x][y].m_HasBeenUpdated)
				{
					m_ParticleContainer[x][y].m_HasBeenUpdated = true;
					EParticleType particleBeneath = GetSurroundingParticleType(EDirection::Bottom, x, y);
					switch (m_ParticleContainer[x][y].m_Type)
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
				m_ParticleContainer[x][y].m_HasBeenUpdated = false;
			}
		}
	}

	void LandscapeComponent::SpawnParticle(EParticleType type, unsigned int x, unsigned int y)
	{
		switch (type)
		{
			case(EParticleType::Sand):
				m_ParticleContainer[x][y] = PARTICLE_SAND;
				break;
		}
	}

	EParticleType LandscapeComponent::GetSurroundingParticleType(EDirection direction, unsigned int centerX, unsigned int centerY) const
	{
		EParticleType type = EParticleType::Border;

		switch (direction)
		{
			case(EDirection::TopLeft):
				if (centerX < ALCHEMIST_LANDSCAPE_HEIGHT - 1 && centerY > 0)
				{
					type = m_ParticleContainer[centerX + 1][centerY - 1].m_Type;
				}
				break;
			case(EDirection::Top):
				if (centerX < ALCHEMIST_LANDSCAPE_HEIGHT - 1)
				{
					type = m_ParticleContainer[centerX + 1][centerY].m_Type;
				}
				break;
			case(EDirection::TopRight):
				if (centerX < ALCHEMIST_LANDSCAPE_HEIGHT - 1 && centerY < ALCHEMIST_LANDSCAPE_WIDTH - 1)
				{
					type = m_ParticleContainer[centerX + 1][centerY + 1].m_Type;
				}
				break;
			case(EDirection::Left):
				if (centerY > 0)
				{
					type = m_ParticleContainer[centerX][centerY - 1].m_Type;
				}
				break;
			case(EDirection::Right):
				if (centerY < ALCHEMIST_LANDSCAPE_WIDTH - 1)
				{
					type = m_ParticleContainer[centerX][centerY + 1].m_Type;
				}
				break;
			case(EDirection::BottomLeft):
				if (centerX > 0 && centerY > 0)
				{
					type = m_ParticleContainer[centerX - 1][centerY - 1].m_Type;
				}
				break;
			case(EDirection::Bottom):
				if (centerX > 0)
				{
					type = m_ParticleContainer[centerX - 1][centerY].m_Type;
				}
				break;
			case(EDirection::BottomRight):
				if (centerX > 0 && centerY < ALCHEMIST_LANDSCAPE_WIDTH - 1)
				{
					type = m_ParticleContainer[centerX - 1][centerY + 1].m_Type;
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
				Color particleColor = GetColorForParticleType(m_ParticleContainer[x][y].m_Type);
				unsigned int basePixelIndex = ((x * ALCHEMIST_LANDSCAPE_WIDTH) + y) * ALCHEMIST_PIXEL_DATA_SIZE;
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
		Particle currentParticle = m_ParticleContainer[x][y];
		if (GetSurroundingParticleType(EDirection::Bottom, x, y) != EParticleType::Border && GetSurroundingParticleType(EDirection::Bottom, x, y) != EParticleType::Sand)
		{
			m_ParticleContainer[x][y] = m_ParticleContainer[x - 1][y];
			m_ParticleContainer[x - 1][y] = currentParticle;
		}
		else if (GetSurroundingParticleType(EDirection::BottomLeft, x, y) != EParticleType::Border && GetSurroundingParticleType(EDirection::BottomLeft, x, y) != EParticleType::Sand)
		{
			m_ParticleContainer[x][y] = m_ParticleContainer[x - 1][y - 1];
			m_ParticleContainer[x - 1][y - 1] = currentParticle;
		}
		else if (GetSurroundingParticleType(EDirection::BottomRight, x, y) != EParticleType::Border && GetSurroundingParticleType(EDirection::BottomRight, x, y) != EParticleType::Sand)
		{
			m_ParticleContainer[x][y] = m_ParticleContainer[x - 1][y + 1];
			m_ParticleContainer[x - 1][y + 1] = currentParticle;
		}
	}

	void LandscapeComponent::UpdateWater(unsigned int x, unsigned int y)
	{
		if (GetSurroundingParticleType(EDirection::Bottom, x, y) == EParticleType::Air)
		{
			m_ParticleContainer[x - 1][y] = m_ParticleContainer[x][y];
			m_ParticleContainer[x][y] = PARTICLE_AIR;
		}
		else if (GetSurroundingParticleType(EDirection::BottomLeft, x, y) == EParticleType::Air)
		{
			m_ParticleContainer[x - 1][y - 1] = m_ParticleContainer[x][y];
			m_ParticleContainer[x][y] = PARTICLE_AIR;
		}
		else if (GetSurroundingParticleType(EDirection::BottomRight, x, y) == EParticleType::Air)
		{
			m_ParticleContainer[x - 1][y + 1] = m_ParticleContainer[x][y];
			m_ParticleContainer[x][y] = PARTICLE_AIR;
		}
		else if (GetSurroundingParticleType(EDirection::Left, x, y) == EParticleType::Air)
		{
			m_ParticleContainer[x][y - 1] = m_ParticleContainer[x][y];
			m_ParticleContainer[x][y] = PARTICLE_AIR;
		}
		else if (GetSurroundingParticleType(EDirection::Right, x, y) == EParticleType::Air)
		{
			m_ParticleContainer[x][y + 1] = m_ParticleContainer[x][y];
			m_ParticleContainer[x][y] = PARTICLE_AIR;
		}
	}
}