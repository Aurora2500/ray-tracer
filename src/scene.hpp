#pragma once
#include "camera.hpp"
#include "config.hpp"
#include "hittable_list.hpp"
#include "renderer.hpp"
#include <mutex>

struct RenderJob {
	int x;
	int y;
	int width;
	int height;
};

class Scene {
private:
	Camera m_camera;
	hittable_list m_world;
	std::vector<RenderJob> m_image_patches;
	std::mutex m_mutex;
	std::thread** m_threads;

public:
	Scene();
	void render(Renderer &renderer);
};