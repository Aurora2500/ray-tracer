#pragma once
#include <thread>

namespace Config {
	const int WIDTH = 1920;
	const int HEIGHT = 1080;
	const int RAYS_PER_PIXEL = 20;
	const int MAX_DEPTH = 50;
	//const int THREADS = std::thread::hardware_concurrency();
	const int THREADS = 12;
	const int PATCH_SIZE = 10;
}