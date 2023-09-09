#pragma once
#include <thread>

namespace Config {
	const int WIDTH = 1920;
	const int HEIGHT = 1080;
	const int BATCH_WIDTH = 120;
	const int BATCH_HEIGHT = 120;
	const int RAYS_PER_PIXEL = 20;
	const int MAX_DEPTH = 50;
	const int THREADS = std::thread::hardware_concurrency();
}