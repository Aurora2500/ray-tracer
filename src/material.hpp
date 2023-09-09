#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include "hittable.hpp"
#include "texture.hpp"

#include <memory>

class material {
public:
	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
	virtual ~material() = default;
};

class lambertian : public material {
private:
	std::shared_ptr<texture> m_albedo;

public:
	lambertian(const vec3 &albedo);
	lambertian(std::shared_ptr<texture> albedo);

	bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const override;
};

class metal : public material {
private:
	vec3 m_albedo;
	double m_fuzz;

public:
	metal(const vec3 &albedo, double fuzz);

	bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const override;
};

#endif