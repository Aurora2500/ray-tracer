#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "app.hpp"
#include "camera.hpp"
#include "hittable_list.hpp"
#include "rand.hpp"
#include "time.hpp"
#include "material.hpp"
#include <cmath>
#include <memory>

const int max_depth = 50;

vec3 ray_col(const ray& r, const hittable& world, int depth) {
	if (depth >= max_depth) return vec3();
	hit_record rec;
	if (world.hit(r, interval(0.00001, INFINITY), rec)) {
		ray scattered;
		vec3 attenuation;
		if(rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return ray_col(scattered, world, depth + 1) * attenuation;
		return vec3();
	}
	double height = r.direction().z();
	height = (height + 1.0) / 2.0;
	vec3 col = vec3(1.0, 1.0, 1.0) * (1-height) + vec3(0.5, 0.7, 1.0) * height;
	return col;
}

Application::Application()
	: m_renderer(),  m_tex(1920, 1080)
{
	m_tex.init();
}

Application::~Application()
{
	glfwTerminate();
}


void Application::run() {
	GLuint texID = m_tex.glTexture();

	vec3 cam_pos(13, 3, 2);

	Camera c(
		cam_pos,
		-cam_pos,
		65.0f,
		(1920.0f / 1080.0f),
		50
	);

	hittable_list world;

	std::cout << "Generating world..." << std::endl;

	auto mat_ground = std::make_shared<lambertian>(vec3(0.8, 0.8, 0.0));

	world.add(std::make_shared<sphere>(vec3(0, 0, -1000), 1000, mat_ground));


	for(int a = -11; a <= 11; a++) {
		for(int b = -11; b <= 11; b++) {
			double mat_chosen = random_double();
			vec3 center(a + 0.9 * random_double(), b + 0.9 * random_double(), 0.2);

			if((center - vec3(4, 0.2, 0)).length() > 0.9) {
				if(mat_chosen < 0.8) {
					auto mat = std::make_shared<lambertian>(vec3(random_double() * random_double(), random_double() * random_double(), random_double() * random_double()));
					world.add(std::make_shared<sphere>(center, 0.2, mat));
				} else {
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

	/*
	auto mat_one = std::make_shared<lambertian>(vec3(0.8, 0.3, 0.3));
	auto mat_two = std::make_shared<lambertian>(vec3(0.8, 0.8, 0.0));
	auto mat_three = std::make_shared<metal>(vec3(0.8, 0.6, 0.2), 0.3);

	// world.add(std::make_shared<sphere>(vec3(0.7, -0.2, 0), 0.5, mat_one));
	//world.add(std::make_shared<sphere>(vec3(0, -1, -100.5), 100, mat_two));
	world.add(std::make_shared<sphere>(vec3(0.7, 0.2, 0), 0.5, mat_three));
	*/

	std::cout << "world aabb "
		<< world.bounding_box()
		<< std::endl;

	std::cout << "world size: " << world.size() << std::endl;

	world.bake();

	std::cout << "world baked aabb "
		<< world.bounding_box()
		<< std::endl;

	std::cout << "Rendering..." << std::endl;

	ray r;

	double dX = (2 / (double)m_tex.width());
	double dY = (2 / (double)m_tex.height());

	const int scanline_height = 10;

	Stopwatch sw_render("Render");
	Stopwatch sw_refresh("Refresh");
	Stopwatch sw_line_render("Line Render");

	sw_render.start();

	Timer timer_render(std::chrono::milliseconds(1000 / 20));

	for(int y = 0; y < m_tex.height(); y++) {
		std::cout << "line " << y << std::endl;
		sw_line_render.start();
		for(int x = 0; x < m_tex.width(); x++) {
			if(timer_render.tick()) {
				if(!m_renderer.should_continue()) {
					return;
				}
				m_renderer.refresh();
			}
			
			if (x == 1020 && y == (1030 - 720)) {
				int mm_a = 0;
			}
			double u = (double)x / (double)m_tex.width() * 2.0 - 1.0;
			double v = (double)y / (double)m_tex.height() * 2.0 - 1.0;
			vec3 col = vec3(0.0, 0.0, 0.0);
			for (int i = 0; i < c.samples(); i++) {
				double dx = (random_double() - 0.5);
				double dy = (random_double() - 0.5);
				double du = dx * dX;
				double dv = dy * dX;
				r = c.get_ray(u + du, v + dv);
				col += ray_col(r, world, 0);
			}
			col /= c.samples();
			m_tex.setPixel(x, y, col);
		}
		sw_line_render.lap();
		if (y % scanline_height == 0 && y != 0) {
			sw_refresh.start();
			m_tex.update(y-scanline_height, scanline_height);
			m_renderer.set_texture(texID);
			m_renderer.refresh();
			if (!m_renderer.should_continue()) {
				return;
			}
			sw_refresh.lap();
		}
	}
	int last_count = ((m_tex.height()-1) % scanline_height) + 1;
	int last_line = m_tex.height() - last_count;
	sw_refresh.start();

	m_tex.update(last_line, last_count);
	m_renderer.set_texture(texID);
	sw_refresh.lap();

	sw_refresh.stop();
	sw_line_render.stop();
	sw_render.stop();

	while (m_renderer.should_continue())
	{
		m_renderer.refresh();
	}
}