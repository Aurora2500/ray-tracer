#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <glad.h>
#include <glad.h>
#include <GLFW/glfw3.h>

class Renderer {
private:
	size_t m_width, m_height;
	GLuint m_vertexbuffer, m_programID;
	GLFWwindow *m_window;

public:
	Renderer();
	~Renderer();

	void set_texture(GLuint texID);
	void refresh();
	void poll_events();
	bool should_continue();
};

#endif