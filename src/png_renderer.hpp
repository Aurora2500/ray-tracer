#pragma once
#include "renderer.hpp"
#include <string>

class PNGRenderer : public Renderer {
private:
	Canvas m_canvas;

public:

	PNGRenderer();
	~PNGRenderer();

	Canvas& canvas() override;
	void finish() override; // Saves the canvas to a file

};