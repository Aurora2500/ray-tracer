#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_
#include <memory>
#include "vec.hpp"

class texture {
public:
	virtual ~texture() = default;

	virtual vec3 value(double u, double v, const vec3& p) const = 0;
};

class solid_color : public texture {
private:
	vec3 m_color;

public:
	solid_color(vec3 col);
	solid_color(double r, double g, double b);

	vec3 value(double u, double v, const vec3& p) const override;
};

class checker_texture : public texture {
private:
	double m_scale;
	std::shared_ptr<texture> m_even;
	std::shared_ptr<texture> m_odd;

public:
	checker_texture(double scale, std::shared_ptr<texture> even, std::shared_ptr<texture> odd);
	checker_texture(double scale, vec3 even, vec3 odd);

	vec3 value(double u, double v, const vec3& p) const override;
};

#endif