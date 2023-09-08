#include "canvas.hpp"
#include <cmath>

Canvas::Canvas(size_t width, size_t height)
	: m_width(width), m_height(height), m_buf(std::vector<float>(width * height * 3))
{
}

size_t Canvas::width() const {
	return m_width;
}

size_t Canvas::height() const {
	return m_height;
}

const float& Canvas::operator[](size_t i) const {
	return m_buf[i];
}

void Canvas::setPixel(size_t x, size_t y, float r, float g, float b) {
	int idx = (x + y * m_width) * 3;
	m_buf[idx] = std::sqrt(r);
	m_buf[idx+1] = std::sqrt(g);
	m_buf[idx+2] = std::sqrt(b);
}

void Canvas::setPixel(size_t x, size_t y, vec3 col) {
	setPixel(x, y, col.x(), col.y(), col.z());
}
