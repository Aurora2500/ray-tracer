#include <stdio.h>
#include "app.hpp"
#include "time.hpp"
#include "scene.hpp"
#include "material.hpp"
#include <memory>
#include "rand.hpp"


Application::Application() {
	m_renderer = std::make_unique<GLRenderer>(&m_scene);
}

void Application::run() {
	m_renderer->finish();
}