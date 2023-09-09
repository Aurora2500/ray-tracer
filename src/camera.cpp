#include "camera.hpp"

#include <cmath>

constexpr double PI = 3.14159265358979323846;

Camera::Camera(
	vec3 origin,
	vec3 dir,
	double vofv,
	double aspect_ratio
) : m_origin(origin),
	m_direction(dir.normalize()),
	m_vfov(vofv),
	m_aspect_ratio(aspect_ratio)
{
}

ray Camera::get_ray(double u, double v) const
{
	vec3 right = cross(m_direction, UP);
	vec3 up = cross(right, m_direction);
	double focal_length = 1.0f / std::tan(m_vfov * PI / 2.0f / 180.0f);

	return ray(
		m_origin,
		(
			m_direction * focal_length
			+ right * (u) * m_aspect_ratio
			+ up * (v)
			).normalize()
	);
}
