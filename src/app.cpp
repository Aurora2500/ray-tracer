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
#include <cmath>

vec3 ray_col(const ray& r, const hittable_list& world) {
	hit_record rec;
	if (world.hit(r, interval(0.0, INFINITY), rec)) {
		vec3 dir = random_on_hemisphere(rec.normal);
		return ray_col(ray(rec.p, dir), world) * 0.5;
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

	Camera c(
		vec3(),
		vec3(0.0f, 1.0f, 0.0f),
		90.0f,
		(1920.0f / 1080.0f),
		10
	);

	hittable_list world;

	world.add(sphere(vec3(0, 1, 0), 0.5));
	world.add(sphere(vec3(0, 0, -100.5), 100));

	ray r;

	double dX = (2 / (double)m_tex.width());
	double dY = (2 / (double)m_tex.height());

	const int scanline_height = 2;

	Stopwatch sw_render("Render");
	Stopwatch sw_refresh("Refresh");
	Stopwatch sw_line_render("Line Render");

	sw_render.start();

	for(int y = 0; y < m_tex.height(); y++) {
		sw_line_render.start();
		for(int x = 0; x < m_tex.width(); x++) {
			double u = (double)x / (double)m_tex.width() * 2.0 - 1.0;
			double v = (double)y / (double)m_tex.height() * 2.0 - 1.0;
			vec3 col = vec3(0.0, 0.0, 0.0);
			for (int i = 0; i < c.samples(); i++) {
				double dx = (random_double() - 0.5);
				double dy = (random_double() - 0.5);
				double du = dx * dX;
				double dv = dy * dX;
				// std::cout << dx << " " << dy << "\n";
				r = c.get_ray(u + du, v + dv);
				col += ray_col(r, world);
			}
			std::cout.flush();
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