#pragma once
#include "camera.hpp"
#include "config.hpp"
#include "hittable_list.hpp"
#include "renderer.hpp"

class Scene {
private:
	Camera m_camera;
	hittable_list m_world;

	vec3 ray_col(const ray& r, int depth) const;

public:
	Scene();
	void render(Renderer &renderer) const;
};