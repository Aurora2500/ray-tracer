#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "app.hpp"
#include "camera.hpp"
#include "hittable_list.hpp"
#include "rand.hpp"
#include <cmath>

vec3 ray_col(const ray& r, const hittable_list& world) {
	hit_record rec;
	if (world.hit(r, interval(0.0, INFINITY), rec)) {
		return (rec.normal + vec3(1.0, 1.0, 1.0)) * 0.5;
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
		1
	);

	hittable_list world;

	world.add(sphere(vec3(0, 1, 0), 0.5));
	world.add(sphere(vec3(0, 0, -100.5), 100));

	ray r;

	double dX = 1 / (double)m_tex.width();
	double dY = 1 / (double)m_tex.height();

	for(int y = 0; y < m_tex.height(); y++) {
		for(int x = 0; x < m_tex.width(); x++) {
			double u = (double)x / (double)m_tex.width() * 2.0 - 1.0;
			double v = (double)y / (double)m_tex.height() * 2.0 - 1.0;
			vec3 col = vec3(0.0, 0.0, 0.0);
			for (int i = 0; i < c.samples(); i++) {
				double du = random_double() * dX;
				double dv = random_double() * dX;
				r = c.get_ray(u + du, v + dv);
				col += ray_col(r, world);
			}
			col /= c.samples();
			m_tex.setPixel(x, y, col);
		}
		if (y % 40 == 0) {
			m_tex.update();
			m_renderer.set_texture(texID);
			m_renderer.refresh();
			if (!m_renderer.should_continue()) {
				return;
			}
		}
	}
	m_tex.update();
	m_renderer.set_texture(texID);

	while (m_renderer.should_continue())
	{
		m_renderer.refresh();
	}
}