#include <stdio.h>
#include "app.hpp"
#include "time.hpp"
#include "scene.hpp"
#include "material.hpp"
#include <memory>
#include "rand.hpp"


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
	
	Stopwatch timer("Render");
	scene.render(m_canvas);
	timer.stop();

	m_canvas.update();
	m_renderer.set_texture(texID);

	while (m_renderer.should_continue())
	{
		m_renderer.refresh();
	}
}