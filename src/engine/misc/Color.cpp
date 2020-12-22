#include "Color.h"

namespace ForgeEngine
{
	Color::Color(float r, float g, float b, float a /*= 1.f*/) :
		m_R(r),
		m_G(g),
		m_B(b),
		m_A(a)
	{
	}

	Color Color::GetGrayScale() const
	{
		return Color{ m_R / 3.f, m_G / 3.f, m_B / 3.f, m_A };
	}

	/*static*/ Color Color::GetGrayScale(Color c)
	{
		return c.GetGrayScale();
	}

	std::ostream& operator<<(std::ostream& os, const Color& c)
	{
		os << "{R" << c.GetR() << ", G" << c.GetG() << ", B" << c.GetB() << ", A" << c.GetA() << "}";
		return os;
	}
}