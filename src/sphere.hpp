#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "hittable.hpp"
#include "vec.hpp"
#include "ray.hpp"
#include <memory>

class sphere : public hittable {
private:
	vec3 m_center;
	double m_radius;
	std::shared_ptr<material> m_mat_ptr;

public:
	sphere(vec3 center, double radius, std::shared_ptr<material> mat_ptr);
	bool hit(const ray &r, interval t_lim, hit_record &rec) const override;
};

#endif