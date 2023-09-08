#pragma once
#include <glad.h>
#include "renderer.hpp"
#include "canvas.hpp"

class GLCanvas : public Canvas {
private:
	GLuint m_glTexture;

public:
	GLCanvas(size_t width, size_t height);
	void init();

	void bind();
	void unbind();
	void update();
	void update(size_t line_offset, size_t line_count);

	friend class GLRenderer;
};

class GLRenderer : public Renderer {
private:
	size_t m_width, m_height;
	GLuint m_vertexbuffer, m_programID;
	GLFWwindow *m_window;
	GLCanvas m_canvas;
	
	void set_texture(GLuint texID);

public:
	GLRenderer();
	~GLRenderer();

	void refresh();
	void poll_events();
	bool should_continue();

	Canvas& canvas() override;

	void finish() override;
};
