#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include "hittable.hpp"

class material {
public:
	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
};

class lambertian : public material {
private:
	vec3 m_albedo;

public:
	lambertian(const vec3 &albedo);

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