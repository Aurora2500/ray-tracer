#include "material.hpp"
#include "vec.hpp"

lambertian::lambertian(const vec3 &albedo)
	: lambertian(std::make_shared<solid_color>(albedo))
{
}

lambertian::lambertian(std::shared_ptr<texture> albedo)
	: m_albedo(albedo)
{
}

bool lambertian::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
{
	vec3 scatter_direction = rec.normal + random_unit_sphere();
	if(scatter_direction.near_zero())
		scatter_direction = rec.normal;
	scattered = ray(rec.p, scatter_direction);
	attenuation = m_albedo->value(rec.u, rec.v, rec.p);
	return true;
}

metal::metal(const vec3 &albedo, double fuzz)
	: m_albedo(albedo), m_fuzz(fuzz)
{
}

bool metal::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
{
	vec3 reflected = reflect(r_in.direction().normalize(), rec.normal);
	scattered = ray(rec.p, reflected + random_unit_sphere() * m_fuzz);
	attenuation = m_albedo;
	return (dot(scattered.direction(), rec.normal) > 0);
}