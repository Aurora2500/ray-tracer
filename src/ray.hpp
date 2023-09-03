#ifndef RAY_HPP_
#define RAY_HPP_

#include "ray.hpp"
#include "vec.hpp"

class ray {
private:
	vec3 m_origin;
	vec3 m_direction;
public:
	ray();
	ray(const vec3 &origin, const vec3 &direction);
	vec3 origin() const;
	vec3 direction() const;
	vec3 at(double t) const;
};

#endif