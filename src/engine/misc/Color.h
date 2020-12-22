#pragma once

#include <iostream>

namespace ForgeEngine
{
	#define COLOR_RED Color{1.f, 0.f, 0.f}
	#define COLOR_GREEN Color{0.f, 1.f, 0.f}
	#define COLOR_BLUE Color{0.f, 0.f, 1.f}
	#define COLOR_BLACK Color{0.f, 0.f, 0.f}
	#define COLOR_WHITE Color{1.f, 1.f, 1.f}

	class Color
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			float m_R{};
			float m_G{};
			float m_B{};
			float m_A{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Color(float r, float g, float b, float a = 1.f);

			float GetR() const { return m_R; }
			float GetG() const { return m_G; }
			float GetB() const { return m_B; }
			float GetA() const { return m_A; }

			static Color GetGrayScale(Color c);
			Color GetGrayScale() const;

			friend std::ostream& operator<<(std::ostream& os, const Color& c);
	};
}