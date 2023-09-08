#include "scene.hpp"
#include "rand.hpp"
#include "texture.hpp"
#include "material.hpp"

Scene::Scene() :
	camera(
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

	world.add(std::make_shared<sphere>(vec3(0, 0, -1000), 1000, mat_ground));


	for (int a = -11; a <= 11; a++) {
		for (int b = -11; b <= 11; b++) {
			double mat_chosen = random_double();
			vec3 center(a + 0.9 * random_double(), b + 0.9 * random_double(), 0.2);

			if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
				if (mat_chosen < 0.8) {
					auto mat = std::make_shared<lambertian>(vec3(random_double() * random_double(), random_double() * random_double(), random_double() * random_double()));
					world.add(std::make_shared<sphere>(center, 0.2, mat));
				}
				else {
					auto mat = std::make_shared<metal>(vec3(0.5 * (1 + random_double()), 0.5 * (1 + random_double()), 0.5 * (1 + random_double())), 0.5 * random_double());
					world.add(std::make_shared<sphere>(center, 0.2, mat));
				}
			}
		}
	}

	auto mat1 = std::make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0);
	world.add(std::make_shared<sphere>(vec3(0, 0, 1), 1.0, mat1));

	auto mat2 = std::make_shared<lambertian>(vec3(0.4, 0.2, 0.1));
	world.add(std::make_shared<sphere>(vec3(4, 0, 1), 1.0, mat2));

	auto mat3 = std::make_shared<metal>(vec3(0.6, 0.1, 0.6), 0.3);
	world.add(std::make_shared<sphere>(vec3(-4, 0, 1), 1.0, mat3));

	std::cout << "world aabb "
		<< world.bounding_box()
		<< std::endl;

	std::cout << "world size: " << world.size() << std::endl;

	world.bake();

	std::cout << "world baked aabb "
		<< world.bounding_box()
		<< std::endl;
}