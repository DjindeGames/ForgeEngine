#pragma once

#include "engine/core/Component.h"
#include "engine/core/Defines.h"
#include "system/misc/Color.h"

#include <array>

namespace ForgeEngine
{
	class Texture;
}

using namespace ForgeEngine;

namespace Alchemist
{
	#define ALCHEMIST_LANDSCAPE_WIDTH 100
	#define ALCHEMIST_LANDSCAPE_HEIGHT 100
	#define ALCHEMIST_PIXEL_DATA_SIZE 3

	#define PARTICLE_AIR Particle{}
	#define PARTICLE_SAND Particle{EParticleType::Sand, false}
	#define PARTICLE_WATER Particle{EParticleType::Water, false}

	struct ParticlePosition
	{
		unsigned short x;
		unsigned short y;
	};

	enum class EParticleType
	{
		Border,
		Air,
		Water,
		Sand
	};

	enum class EDirection
	{
		TopLeft,
		Top,
		TopRight,
		Left,
		Right,
		BottomLeft,
		Bottom,
		BottomRight
	};

	struct Particle
	{
		EParticleType m_Type = EParticleType::Air;
		bool m_HasBeenUpdated = false;
	};

	class LandscapeComponent : public Component
	{
		using Mother = Component;

		using ParticleContainer = Particle[ALCHEMIST_LANDSCAPE_WIDTH][ALCHEMIST_LANDSCAPE_HEIGHT];

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			ParticleContainer m_ParticleContainer;
			float m_Pixels[ALCHEMIST_LANDSCAPE_WIDTH * ALCHEMIST_LANDSCAPE_HEIGHT * ALCHEMIST_PIXEL_DATA_SIZE];
			std::unique_ptr<Texture> m_Texture;

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			virtual bool OnPreInit() override;
			virtual void OnPreUpdate(float dT) override;

			void SpawnParticle(EParticleType type, unsigned int x, unsigned int y);

		private:
			EParticleType GetSurroundingParticleType(EDirection direction, unsigned int centerX, unsigned int centerY) const;
			void UpdateParticles();
			void DrawTexture();
			Color GetColorForParticleType(EParticleType type) const;
			void GeneratePixels();

			void UpdateSand(unsigned int x, unsigned int y);
			void UpdateWater(unsigned int x, unsigned int y);
	};
}