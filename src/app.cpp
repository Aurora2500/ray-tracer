#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "app.hpp"

Application::Application()
	: m_renderer(),  m_tex(1920, 1080)
{
	for(int y = 0; y < m_tex.height(); y++) {
		for(int x = 0; x < m_tex.width(); x++) {
			float r = (x < (m_tex.width() / 2)) ? 1.0f : 0.0f;
			float g = 0.5f;
			float b = ((float)x / m_tex.width());
			m_tex.setPixel(x, y, r, g, b);
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