#include "scene.hpp"
#include "rand.hpp"
#include "texture.hpp"
#include "material.hpp"
#include "quad.hpp"

#include "job_manager.hpp"
#include <cmath>

vec3 Scene::ray_col(const ray &r, int depth) const
{
	if (depth >= Config::MAX_DEPTH) return vec3();
	hit_record rec;
	if (m_world.hit(r, interval(0.00001, INFINITY), rec)) {
		ray scattered;
		vec3 attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return ray_col(scattered, depth + 1) * attenuation;
		return vec3();
	}
	double height = r.direction().z();
	height = (height + 1.0) / 2.0;
	vec3 col = vec3(1.0, 1.0, 1.0) * (1 - height) + vec3(0.5, 0.7, 1.0) * height;
	return col;
	return vec3();
}

Scene::Scene()
: m_camera(
	 vec3(13, 3, 2),
	 -vec3(13, 3, 2),
	 65.0f,
	 Config::WIDTH / (float)Config::HEIGHT,
	 Config::RAYS_PER_PIXEL
	)
{
	std::cout << "Generating world..." << std::endl;

	auto checker = std::make_shared<checker_texture>(1 / 0.32, vec3(0.2, 0.3, 0.1), vec3(0.9, 0.9, 0.9));

	auto mat_ground = std::make_shared<lambertian>(checker);

	m_world.add(std::make_shared<sphere>(vec3(0, 0, -1000), 1000, mat_ground));


	for (int a = -11; a <= 11; a++) {
		for (int b = -11; b <= 11; b++) {
			double mat_chosen = random_double();
			vec3 center(a + 0.9 * random_double(), b + 0.9 * random_double(), 0.2);

			if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
				if (mat_chosen < 0.8) {
					auto mat = std::make_shared<lambertian>(vec3(random_double() * random_double(), random_double() * random_double(), random_double() * random_double()));
					m_world.add(std::make_shared<sphere>(center, 0.2, mat));
				}
				else {
					auto mat = std::make_shared<metal>(vec3(0.5 * (1 + random_double()), 0.5 * (1 + random_double()), 0.5 * (1 + random_double())), 0.5 * random_double());
					m_world.add(std::make_shared<sphere>(center, 0.2, mat));
				}
			}
		}
	}

	auto mat1 = std::make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0);
	m_world.add(std::make_shared<sphere>(vec3(0, 0, 1), 1.0, mat1));

	auto mat2 = std::make_shared<lambertian>(vec3(0.4, 0.2, 0.1));
	m_world.add(std::make_shared<sphere>(vec3(4, 0, 1), 1.0, mat2));

	auto mat3 = std::make_shared<metal>(vec3(0.6, 0.1, 0.6), 0.3);
	m_world.add(std::make_shared<sphere>(vec3(-4, 0, 1), 1.0, mat3));

	auto left_red = std::make_shared<lambertian>(vec3(1.0, 0.2, 0.2));

	m_world.add(std::make_shared<quad>(vec3(-3, -2, 5), vec3(0, 0, -4), vec3(0, 4, 0), left_red));

	std::cout << "world size: " << m_world.size() << std::endl;

	m_world.bake();
}

struct RenderJob {
	int x;
	int y;
	int width;
	int height;
};


void Scene::render(Renderer &renderer) const
{
	RendererSubscription subscription;
	Canvas &canvas = renderer.canvas();
	renderer.add_subscription(subscription);

	JobManager<RenderJob> job_manager(Config::THREADS, [this, &canvas](RenderJob job) {
		double dX = 2 / (double)Config::WIDTH;
		double dY = 2 / (double)Config::HEIGHT;
		for (int y = job.y; y < job.y + job.height; y++) {
			for(int x = job.x; x < job.x + job.width; x++) {
				double u = (double)x / (double)Config::WIDTH * 2.0 - 1.0;
				double v = (double)y / (double)Config::HEIGHT * 2.0 - 1.0;
				vec3 col = vec3(0.0, 0.0, 0.0);
				for (int i = 0; i < Config::RAYS_PER_PIXEL; i++) {
					double dx = (random_double() - 0.5);
					double dy = (random_double() - 0.5);
					double du = dx * dX;
					double dv = dy * dX;
					ray r = m_camera.get_ray(u + du, v + dv);
					col += ray_col(r, 0);
				}
				col /= Config::RAYS_PER_PIXEL;
				canvas.setPixel(x, y, col);
			}
		}
	});

	for (int y = 0; y < Config::HEIGHT; y += Config::BATCH_HEIGHT) {
		for (int x = 0; x < Config::WIDTH; x += Config::BATCH_WIDTH) {
			int width = std::min(Config::BATCH_WIDTH, Config::WIDTH - x);
			int height = std::min(Config::BATCH_HEIGHT, Config::HEIGHT - y);
			job_manager.add_job({x, y, width, height});
		}
	}

	using namespace std::chrono_literals;
	job_manager.finish(100ms, subscription.tick);
}
