#include "app.hpp"
#include "camera.hpp"
#include "gl_renderer.hpp"

int main()
{
	GLRenderer renderer;
	Application app(std::make_unique<GLRenderer>(renderer));
	app.run();
}