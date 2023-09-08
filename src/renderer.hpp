#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <glad.h>
#include <GLFW/glfw3.h>
#include "canvas.hpp"

class Renderer {
public:
	virtual ~Renderer() = default;
	virtual Canvas& canvas() = 0;
	virtual void finish() = 0;
};

#endif
