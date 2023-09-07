#ifndef CANVAS_HPP_
#define CANVAS_HPP_
#include "vec.hpp"

#include <cstdint>
#include <stddef.h>

#include <glad.h>

class Canvas {
private:
	float *m_buf;
	size_t m_width, m_height;
	GLuint m_glTexture;
	
public:
	Canvas() = delete;
	Canvas(size_t width, size_t height);
	~Canvas();

	void init();

	size_t width() const;
	size_t height() const;

	GLuint glTexture() const;

	float& operator[](size_t i) const;
	void setPixel(size_t x, size_t y, float r, float g, float b);
	void setPixel(size_t x, size_t y, vec3 col);

	void bind();
	void unbind();
	void update();
	void update(size_t line_offset, size_t line_count);
};

#endif