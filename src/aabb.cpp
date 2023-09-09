#include "aabb.hpp"

aabb::aabb()
{
}

aabb::aabb(const interval &x, const interval &y, const interval &z)
	: x(x), y(y), z(z)
{
}

aabb::aabb(const vec3 &a, const vec3 &b)
	: x(std::min(a.x(), b.x()), std::max(a.x(), b.x()))
	, y(std::min(a.y(), b.y()), std::max(a.y(), b.y()))
	, z(std::min(a.z(), b.z()), std::max(a.z(), b.z()))
{
}

aabb::aabb(const aabb &a, const aabb &b)
	: x(interval(a.x, b.x))
	, y(interval(a.y, b.y))
	, z(interval(a.z, b.z))
{
}

const interval &aabb::axis(int n) const
{
	switch (n)
	{
	default:
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}
}

bool aabb::hit(const ray &r, interval ray_t) const
{
	for (int a = 0; a < 3; a++) {
		double invD = 1.0 / r.direction()[a];
		double orig = r.origin()[a];

		double t0 = (axis(a).min - orig) * invD;
		double t1 = (axis(a).max - orig) * invD;

		if (invD < 0.0)
			std::swap(t0, t1);

		if (t0 > ray_t.min) ray_t.min = t0;
		if (t1 < ray_t.max) ray_t.max = t1;

		if (ray_t.max <= ray_t.min)
			return false;
	}
	return true;
}

std::ostream &operator<<(std::ostream &os, const aabb &a)
{
	os << "aabb(" << a.x.min << ", " << a.y.min << ", " << a.z.min << ")"
		<< " -> "
		<< "(" << a.x.max << ", " << a.y.max << ", " << a.z.max << ")";
	return os;
}

aabb aabb::pad() {
	// Return an AABB that has no side narrower than some delta, padding if necessary.
	double delta = 0.0001;
	interval new_x = (x.size() >= delta) ? x : x.expand(delta);
	interval new_y = (y.size() >= delta) ? y : y.expand(delta);
	interval new_z = (z.size() >= delta) ? z : z.expand(delta);

	return aabb(new_x, new_y, new_z);
}