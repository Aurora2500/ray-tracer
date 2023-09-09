#include "texture.hpp"

#include <cmath>

solid_color::solid_color(vec3 col)
	: m_color(col)
{
}

solid_color::solid_color(double r, double g, double b)
	: solid_color(vec3(r, g, b))
{
}

vec3 solid_color::value(double u, double v, const vec3& p) const {
	(void) u;
	(void) v;
	(void) p;
	return m_color;
}

checker_texture::checker_texture(double scale, std::shared_ptr<texture> even, std::shared_ptr<texture> odd)
	: m_scale(scale), m_even(even), m_odd(odd)
{
}

checker_texture::checker_texture(double scale, vec3 even, vec3 odd)
	: checker_texture(scale, std::make_shared<solid_color>(even), std::make_shared<solid_color>(odd))
{
}

vec3 checker_texture::value(double u, double v, const vec3 &p) const
{
	int x = static_cast<int>(std::floor(p.x() * m_scale));
	int y = static_cast<int>(std::floor(p.y() * m_scale));
	int z = static_cast<int>(std::floor(p.z() * m_scale));

	bool even = (x + y + z) % 2 == 0;

	return even ? m_even->value(u, v, p) : m_odd->value(u, v, p);
}
