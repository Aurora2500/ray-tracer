#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "hittable.hpp"
#include "vec.hpp"
#include "ray.hpp"

class sphere : public hittable {
private:
	vec3 m_center;
	double m_radius;

public:
	sphere(vec3 center, double radius);
	bool hit(const ray &r, interval t_lim, hit_record &rec) const override;
};

#endif