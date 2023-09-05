#ifndef HIT_HPP_
#define HIT_HPP_
#include "vec.hpp"
#include "ray.hpp"
#include "interval.hpp"
#include <memory>

class material;

struct hit_record {
	vec3 p, normal;
	double t;
	std::shared_ptr<material> mat_ptr;
};

class hittable {
public:
	virtual ~hittable() = default;
	virtual bool hit(const ray &r, interval t_lim, hit_record &rec) const = 0;
};

#endif