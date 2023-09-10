#ifndef APP_HPP_
#define APP_HPP_

#include "renderer.hpp"
#include "canvas.hpp"
#include <GLFW/glfw3.h>
#include "scene.hpp"
#include "gl_renderer.hpp"
#include <memory>

class Application {
private:
	
	Scene m_scene;
	std::unique_ptr<Renderer> m_renderer;

public:
	Application();

	void run();
};

#endif