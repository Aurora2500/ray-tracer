#pragma once
#include "scene.hpp"
#include "canvas.hpp"
#include <mutex>

struct RenderJob {
	int x;
	int y;
	int width;
	int height;
};

class Raytracer {
public:

	Raytracer(Scene* scene, Canvas* canvas);
	void render();
	void tick();

private:
	
	Canvas* m_canvas;
	std::mutex m_mutex;
	std::thread** m_threads;
	std::vector<RenderJob> m_jobs;
	Scene* m_scene;

};