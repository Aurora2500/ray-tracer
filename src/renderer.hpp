#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

class Rendered {
private:
	GLFWwindow *m_window;

public:
	Rendered();
	~Rendered();

	void refresh();
	void should_close();
};

#endif