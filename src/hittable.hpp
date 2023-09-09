#ifndef HIT_HPP_
#define HIT_HPP_
#include "vec.hpp"
#include "ray.hpp"
#include "interval.hpp"
#include "aabb.hpp"
#include <memory>

class material;

struct hit_record {
	vec3 p, normal;
	double t;
	std::shared_ptr<material> mat_ptr;
	double u, v;

	void set_face_normal(const ray& r, const vec3& outward_normal) {
		bool front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable {
public:
	virtual ~hittable() = default;
	virtual bool hit(const ray &r, interval t_lim, hit_record &rec) const = 0;
	virtual aabb bounding_box() const = 0;
};

#endif