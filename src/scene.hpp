#pragma once
#include "camera.hpp"
#include "config.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "scene.hpp"
#include "rand.hpp"
#include "texture.hpp"
#include "material.hpp"
#include "quad.hpp"

class Scene {
public:
	Scene();

	Camera camera;
	hittable_list world;

};