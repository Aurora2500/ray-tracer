#ifndef CAMERA_HPP_
#define CAMERA_HPP_
#include "vec.hpp"
#include "ray.hpp"

class Camera {
private:
	vec3 m_origin, m_direction;
	double m_vfov;
	double m_aspect_ratio;
	
public:
	Camera(vec3 origin, vec3 dir, double vfov, double aspect_ratio, int samples_per_pixel);

	ray get_ray(double u, double v) const;
};

#endif