#include "app.hpp"
#include "camera.hpp"
#include "png_renderer.hpp"

int main()
{
	PNGRenderer renderer;
	Application app(std::make_unique<PNGRenderer>(renderer));
	app.run();
}