#include <stdio.h>
#include "app.hpp"
#include "time.hpp"
#include "scene.hpp"
#include "material.hpp"
#include <memory>
#include "rand.hpp"

vec3 ray_col(const ray& r, const hittable& world, int depth) {
	if (depth >= Config::MAX_DEPTH) return vec3();
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
	: m_renderer(),  m_canvas(Config::WIDTH, Config::HEIGHT)
{
	m_canvas.init();
}

Application::~Application()
{
	glfwTerminate();
}


void Application::run() {
	GLuint texID = m_canvas.glTexture();

	Scene scene;

	/*
	auto mat_one = std::make_shared<lambertian>(vec3(0.8, 0.3, 0.3));
	auto mat_two = std::make_shared<lambertian>(vec3(0.8, 0.8, 0.0));
	auto mat_three = std::make_shared<metal>(vec3(0.8, 0.6, 0.2), 0.3);

	// world.add(std::make_shared<sphere>(vec3(0.7, -0.2, 0), 0.5, mat_one));
	//world.add(std::make_shared<sphere>(vec3(0, -1, -100.5), 100, mat_two));
	world.add(std::make_shared<sphere>(vec3(0.7, 0.2, 0), 0.5, mat_three));
	*/

	
	ray r;

	double dX = (2 / (double)m_canvas.width());
	double dY = (2 / (double)m_canvas.height());

	const int scanline_height = 10;

	Stopwatch sw_render("Render");
	Stopwatch sw_refresh("Refresh");
	Stopwatch sw_line_render("Line Render");

	sw_render.start();

	Timer timer_render(std::chrono::milliseconds(1000 / 20));

	for(int y = 0; y < m_canvas.height(); y++) {
		std::cout << "line " << y << std::endl;
		sw_line_render.start();
		for(int x = 0; x < m_canvas.width(); x++) {
			if(timer_render.tick()) {
				if(!m_renderer.should_continue()) {
					return;
				}
				m_renderer.refresh();
			}
			
			if (x == 1020 && y == (1030 - 720)) {
				int mm_a = 0;
			}
			double u = (double)x / (double)m_canvas.width() * 2.0 - 1.0;
			double v = (double)y / (double)m_canvas.height() * 2.0 - 1.0;
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
			m_canvas.setPixel(x, y, col);
		}
		sw_line_render.lap();
		if (y % scanline_height == 0 && y != 0) {
			sw_refresh.start();
			m_canvas.update(y-scanline_height, scanline_height);
			m_renderer.set_texture(texID);
			m_renderer.refresh();
			if (!m_renderer.should_continue()) {
				return;
			}
			sw_refresh.lap();
		}
	}
	int last_count = ((m_canvas.height()-1) % scanline_height) + 1;
	int last_line = m_canvas.height() - last_count;
	sw_refresh.start();

	m_canvas.update(last_line, last_count);
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