#ifndef APP_HPP_
#define APP_HPP_

#include "renderer.hpp"
#include "canvas.hpp"
#include <GLFW/glfw3.h>

class Application {
private:
	Renderer m_renderer;
	Canvas m_canvas;

public:
	Application();
	~Application();

	void run();
};

#endif