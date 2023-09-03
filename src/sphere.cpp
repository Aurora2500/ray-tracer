#include "sphere.hpp"
#include <cmath>

sphere::sphere(vec3 center, double radius)
	: m_center(center), m_radius(radius)
{
}

bool sphere::hit(const ray &r, interval t_lim, hit_record &rec) const
{
	vec3 oc = r.origin() - m_center;
	double a = dot(r.direction(), r.direction());
	double half_b = dot(oc, r.direction());
	double c = dot(oc, oc) - m_radius * m_radius;

	double discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;

	double sqrtd = std::sqrt(discriminant);
	double root = (-half_b - sqrtd) / a;
	if (!t_lim.containsOpen(root)) {
		root = (-half_b + sqrtd) / a;
		if (!t_lim.containsOpen(root)) {
			return false;
		}
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	rec.normal = (rec.p - m_center) / m_radius;

	return true;
}