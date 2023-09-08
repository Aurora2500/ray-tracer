#pragma once
#include "camera.hpp"
#include "config.hpp"
#include "hittable_list.hpp"

class Scene {
public:
	
	Scene();

	Camera camera;
	hittable_list world;

};