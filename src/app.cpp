#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "app.hpp"
#include "camera.hpp"

bool hit_sphere(vec3 center, double radius, const ray& r) {
	vec3 oc = r.origin() - center;
	double a = dot(r.direction(), r.direction());
	double b = 2.0 * dot(oc, r.direction());
	double c = dot(oc, oc) - radius * radius;
	double discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

Application::Application()
	: m_renderer(),  m_tex(1920, 1080)
{
	Camera c(
		vec3(),
		vec3(0.0f, 1.0f, 0.0f),
		90.0f,
		(1920.0f / 1080.0f)
	);

	ray r;

	for(int y = 0; y < m_tex.height(); y++) {
		for(int x = 0; x < m_tex.width(); x++) {
			double u = (double)x / (double)m_tex.width() * 2.0 - 1.0;
			double v = (double)y / (double)m_tex.height() * 2.0 - 1.0;
			r = c.get_ray(u, v);
			if(hit_sphere(vec3(0, 1, 0), 0.5, r)) {
				m_tex.setPixel(x, y, 1.0, 0.0, 0.0);
				continue;
			}
			double height = r.direction().z();
			height = (height + 1.0) / 2.0;
			vec3 col = vec3(1.0, 1.0, 1.0) * (1-height) + vec3(0.5, 0.7, 1.0) * height;
			m_tex.setPixel(x, y, col);
		}
	}

	m_tex.init();
	m_tex.update();
}

Application::~Application()
{
	glfwTerminate();
}


void Application::run() {
	GLuint texID = m_tex.glTexture();
	m_renderer.set_texture(texID);

	while (m_renderer.should_continue())
	{
		m_renderer.refresh();
	}
}