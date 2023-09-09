#pragma once
#include "channel.hpp"
#include "subscription.hpp"
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <iostream>

template <typename T>
class JobManager {
private:
	std::vector<std::thread> m_threads;
	Sender<T> m_sender;
	std::function<void(T)> m_job;
	int m_num_running;

	std::mutex m_running_mutex;
	std::condition_variable m_running_cv;
public:
	~JobManager() {
		for (auto& thread : m_threads) {
			thread.join();
		}
	}
	JobManager(int num_threads, std::function<void(T)> job)
		: m_threads(num_threads)
		, m_job(job)
	{
		m_num_running = num_threads;
		auto [tx, rx] = channel<T>();
		m_sender = tx;
		int i = 0;
		for (auto& thread : m_threads) {
			i++;
			thread = std::thread([rx, i, this]() {
				// TODO: fix this data race
				// without the sleep some threads end early, making it not use all of the CPU.
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				while (true) {
					auto value = rx.receive();
					if (!value) {
						break;
					}
					m_job(*value);
				}
				std::unique_lock<std::mutex> lock(m_running_mutex);
				m_num_running--;
				m_running_cv.notify_one();
			});
		}
	}

	void add_job(T job) {
		m_sender.send(job);
	}

	void finish(std::chrono::duration<int, std::milli> tick, Subscription& subscription) {
		// delete the sender, making the receivers stop
		m_sender = Sender<T>();
		// wait for threads to finish
		std::unique_lock<std::mutex> lock(m_running_mutex);
		while(m_num_running > 0) {
			subscription.notify();
			m_running_cv.wait_for(lock, tick);
		}
	}
};