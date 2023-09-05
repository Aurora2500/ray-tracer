#include "sphere.hpp"
#include <cmath>

sphere::sphere(vec3 center, double radius, std::shared_ptr<material> mat_ptr)
	: m_center(center), m_radius(radius), m_mat_ptr(mat_ptr)
{
	vec3 rvec = vec3(radius, radius, radius);
	m_bbox = aabb(center - rvec, center + rvec);
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
	rec.mat_ptr = m_mat_ptr;

	return true;
}

aabb sphere::bounding_box() const
{
	return m_bbox;
}
