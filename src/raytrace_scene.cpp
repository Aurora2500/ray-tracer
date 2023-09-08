#include "raytrace_scene.hpp"
#include "rand.hpp"
#include "material.hpp"

vec3 ray_col(const ray& r, const hittable& world, int depth) {
	if (depth >= Config::MAX_DEPTH) return vec3();
	hit_record rec;
	if (world.hit(r, interval(0.00001, INFINITY), rec)) {
		ray scattered;
		vec3 attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return ray_col(scattered, world, depth + 1) * attenuation;
		return vec3();
	}
	double height = r.direction().z();
	height = (height + 1.0) / 2.0;
	vec3 col = vec3(1.0, 1.0, 1.0) * (1 - height) + vec3(0.5, 0.7, 1.0) * height;
	return col;
}

void raytrace_scene(const Scene& scene, float* buffer) {
	ray r;

	double dX = 2 / (double)Config::WIDTH;
	double dY = 2 / (double)Config::HEIGHT;

	for (int y = 0; y < Config::HEIGHT; y++) {
		std::cout << "line " << y << std::endl;
		for (int x = 0; x < Config::WIDTH; x++) {
			double u = (double)x / (double)Config::WIDTH * 2.0 - 1.0;
			double v = (double)y / (double)Config::HEIGHT * 2.0 - 1.0;
			vec3 col = vec3(0.0, 0.0, 0.0);
			for (int i = 0; i < Config::RAYS_PER_PIXEL; i++) {
				double dx = (random_double() - 0.5);
				double dy = (random_double() - 0.5);
				double du = dx * dX;
				double dv = dy * dX;
				r = scene.camera.get_ray(u + du, v + dv);
				col += ray_col(r, scene.world, 0);
			}
			col /= Config::RAYS_PER_PIXEL;
			int idx = (x + y * Config::WIDTH) * 3;
			buffer[idx] = col.x();
			buffer[idx + 1] = col.y();
			buffer[idx + 2] = col.z();
		}
	}
}