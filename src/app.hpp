#ifndef APP_HPP_
#define APP_HPP_

#include "renderer.hpp"
#include "canvas.hpp"
#include <GLFW/glfw3.h>
#include <memory>

class Application {
private:
	std::unique_ptr<Renderer> m_renderer;

public:
	Application() = delete;
	Application(std::unique_ptr<Renderer> renderer);

	void run();
};

#endif