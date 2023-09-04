#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_
#include "vec.hpp"

#include <cstdint>
#include <stddef.h>

#include<GL/glew.h>
#include<GL/gl.h>

class Texture {
private:
	float *m_buf;
	size_t m_width, m_height;
	GLuint m_glTexture;
	
public:
	Texture() = delete;
	Texture(size_t width, size_t height);
	~Texture();

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