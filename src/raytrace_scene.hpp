#pragma once

#include "scene.hpp"

vec3 ray_col(const ray& r, const hittable& world, int depth);
void raytrace_scene(const Scene& scene, float* buffer);