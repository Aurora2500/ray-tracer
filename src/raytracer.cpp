#include "raytracer.hpp"
#include "time.hpp"

static bool is_thread_idle[Config::THREADS];

Raytracer::Raytracer(Scene* scene, Canvas* canvas) {
	m_scene = scene;
	m_canvas = canvas;
}

vec3 ray_col(const ray &r, int depth, const hittable_list* world)
{
	if (depth >= Config::MAX_DEPTH) return vec3();
	hit_record rec;
	if (world->hit(r, interval(0.00001, INFINITY), rec)) {
		ray scattered;
		vec3 attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return ray_col(scattered, depth + 1, world) * attenuation;
		return vec3();
	}
	double height = r.direction().z();
	height = (height + 1.0) / 2.0;
	vec3 col = vec3(1.0, 1.0, 1.0) * (1 - height) + vec3(0.5, 0.7, 1.0) * height;
	return col;
	return vec3();
}

void worker_routine(hittable_list* world, Camera* camera, Canvas* canvas, std::deque<RenderJob>* jobs, std::mutex* mutex, int thread_index) {
	RenderJob job;

	while (true) {
		// Lock the mutex and find a job to do
		mutex->lock();
		if (jobs->size() > 0) {
			job = jobs->back();
			jobs->pop_back();
		}
		else {
			// If there are no more jobs to be done just leave
			std::cout << "Finished rendering" << std::endl;
			is_thread_idle[thread_index] = true;
			mutex->unlock();
			return;
		}
		mutex->unlock();

		// Do the job
		double dX = 2 / (double)Config::WIDTH;
		double dY = 2 / (double)Config::HEIGHT;

		for (int y = job.y; y < job.y + job.height; y++) {
			for (int x = job.x; x < job.x + job.width; x++) {
				double u = (double)x / (double)Config::WIDTH * 2.0 - 1.0;
				double v = (double)y / (double)Config::HEIGHT * 2.0 - 1.0;
				vec3 col = vec3(0.0, 0.0, 0.0);
				for (int i = 0; i < Config::RAYS_PER_PIXEL; i++) {
					double dx = (random_double() - 0.5);
					double dy = (random_double() - 0.5);
					double du = dx * dX;
					double dv = dy * dY;
					ray r = camera->get_ray(u + du, v + dv);
					col += ray_col(r, 0, world);
				}
				col /= Config::RAYS_PER_PIXEL;
				canvas->setPixel(x, y, col);
			}
		}
	}
}

void Raytracer::render() {
	m_threads = new std::thread * [Config::THREADS];
	for (int y = 0; y < Config::HEIGHT; y += Config::PATCH_SIZE) {
		for (int x = 0; x < Config::WIDTH; x += Config::PATCH_SIZE) {
			int width = std::min(Config::PATCH_SIZE, Config::WIDTH - x);
			int height = std::min(Config::PATCH_SIZE, Config::HEIGHT - y);
			m_jobs.push_front({x, y, width, height});
		}
	}

	for (int i = 0; i < Config::THREADS; i++) {
		m_threads[i] = new std::thread(worker_routine, &m_scene->world, &m_scene->camera, m_canvas, &m_jobs, &m_mutex, i);
		is_thread_idle[i] = false;
	}
}

void Raytracer::tick() {
	m_mutex.lock();
	for (int i = 0; i < Config::THREADS; i++) {
		if (!is_thread_idle[i]) {
			m_mutex.unlock();
			return;
		}
	}
	m_mutex.unlock();

	// If all threads are idle, then destroy them all(unless you've destroyed them already)
	if (m_threads == nullptr) {
		return;
	}
	for (int i = 0; i < Config::THREADS; i++) {
		m_threads[i]->join();
		delete m_threads[i];
	}
	delete[] m_threads;
	m_threads = nullptr;
}