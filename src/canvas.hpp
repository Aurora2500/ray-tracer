#ifndef CANVAS_HPP_
#define CANVAS_HPP_
#include "vec.hpp"

#include <cstdint>
#include <vector>
#include <stddef.h>

#include <glad.h>

class Canvas {
protected:
	std::vector<float> m_buf;
	size_t m_width, m_height;
	
public:
	Canvas() = delete;
	Canvas(size_t width, size_t height);
	virtual ~Canvas() = default;

	size_t width() const;
	size_t height() const;

	const float& operator[](size_t i) const;
	void setPixel(size_t x, size_t y, float r, float g, float b);
	void setPixel(size_t x, size_t y, vec3 col);
};

#endif