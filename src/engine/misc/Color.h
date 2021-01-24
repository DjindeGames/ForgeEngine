#pragma once

#include <iostream>

namespace ForgeEngine
{
	#define COLOR_RED			Color{255, 0, 0}
	#define COLOR_GREEN			Color{0, 255, 0}
	#define COLOR_BLUE			Color{0, 0, 255}
	#define COLOR_YELLOW		Color{255, 255, 0}
	#define COLOR_CYAN			Color{0, 255, 255}
	#define COLOR_MAGENTA		Color{255, 0, 255}
	#define COLOR_ORANGE		Color{255, 128, 0}
	#define COLOR_PURPLE		Color{128, 0, 255}
	#define COLOR_SKY_BLUE		Color{27, 142, 250}
	#define COLOR_BLACK			Color{0, 0, 0}
	#define COLOR_WHITE			Color{255, 255, 255}

	class Color
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			unsigned int m_R{};
			unsigned int m_G{};
			unsigned int m_B{};
			float m_A{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Color(unsigned int r, unsigned int g, unsigned int b, float a = 255);

			unsigned int GetR() const { return m_R; }
			unsigned int GetG() const { return m_G; }
			unsigned int GetB() const { return m_B; }
			float GetA() const { return m_A; }

			float GetRRatio() const { return m_R / 255.f; }
			float GetGRatio() const { return m_G / 255.f; }
			float GetBRatio() const { return m_B / 255.f; }

			static Color GetGrayScale(Color c);
			Color GetGrayScale() const;

			friend std::ostream& operator<<(std::ostream& os, const Color& c);
	};
}