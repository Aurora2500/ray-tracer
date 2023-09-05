#include "texture.hpp"
#include <cmath>

Texture::Texture(size_t width, size_t height)
	: m_width(width), m_height(height), m_buf(new float[width * height * 3])
{

}

Texture::~Texture()
{
	delete[] m_buf;
}

void Texture::init() {
	glGenTextures(1, &m_glTexture);
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_FLOAT, nullptr);
	unbind();
}

size_t Texture::width() const {
	return m_width;
}

size_t Texture::height() const {
	return m_height;
}

GLuint Texture::glTexture() const {
	return m_glTexture;
}

float& Texture::operator[](size_t i) const {
	return m_buf[i];
}

void Texture::setPixel(size_t x, size_t y, float r, float g, float b) {
	int idx = (x + y * m_width) * 3;
	m_buf[idx] = std::sqrt(r);
	m_buf[idx+1] = std::sqrt(g);
	m_buf[idx+2] = std::sqrt(b);
}

void Texture::setPixel(size_t x, size_t y, vec3 col) {
	setPixel(x, y, col.x(), col.y(), col.z());
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, m_glTexture);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::update() {
	bind();
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RGB, GL_FLOAT, m_buf);
	unbind();
}

void Texture::update(size_t line_offset, size_t line_count) {
	bind();
	float *line_buf = m_buf + line_offset * m_width * 3;
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, line_offset, m_width, line_count, GL_RGB, GL_FLOAT, line_buf);
	unbind();
}