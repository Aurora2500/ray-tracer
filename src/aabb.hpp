#ifndef AABB_HPP_
#define AABB_HPP_

#include "interval.hpp"
#include "vec.hpp"
#include "ray.hpp"
#include <iostream>

class aabb {
public:
	interval x, y, z;

	aabb();
	aabb(const interval &x, const interval &y, const interval &z);
	aabb(const vec3 &a, const vec3 &b);
	aabb(const aabb &a, const aabb &b);

	const interval& axis(int n) const;

	bool hit(const ray& r, interval ray_t) const;

	double volume() const;
};

std::ostream &operator<<(std::ostream &os, const aabb &a);

#endif