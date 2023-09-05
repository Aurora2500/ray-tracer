#include "time.hpp"
#include <iostream>

Stopwatch::Stopwatch()
	: m_label("Stopwatch"), m_laps(0), m_mean(0.0), m_var(0.0)
{
}

Stopwatch::Stopwatch(std::string label)
	: m_label(label), m_laps(0), m_mean(0.0), m_var(0.0)
{
}

void Stopwatch::start()
{
	m_lap = std::chrono::steady_clock::now();
}

void Stopwatch::lap()
{
	auto end = std::chrono::steady_clock::now();
	auto diff = end - m_lap;
	double time = std::chrono::duration<double, std::milli>(diff).count();
	m_mean = (m_mean * m_laps + time) / (m_laps + 1);
	m_var = (m_var * m_laps + (time - m_mean) * (time - m_mean)) / (m_laps + 1);
	m_laps++;
}

void Stopwatch::stop()
{
	if(m_laps == 0) {
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> duration = end - m_lap;
		std::cout
			<< "Stopwatch "
			<< m_label
			<< " took "
			<< duration.count() * 1000.0
			<< "ms"
			<< std::endl;
		return;
	}
	std::cout
		<< "Stopwatch "
		<< m_label
		<< " has "
		<< m_laps
		<< " laps and took on average "
		<< m_mean
		<< "ms with a variance of "
		<< m_var
		<< "ms"
		<< " for a total of "
		<< m_mean * m_laps
		<< "ms"
		<< std::endl;
}

Timer::Timer(std::chrono::duration<double> period)
	: m_period(period)
{
	m_last = std::chrono::steady_clock::now();
}

bool Timer::tick()
{
	auto now = std::chrono::steady_clock::now();
	auto diff = now - m_last;
	if (diff > m_period) {
		m_last = now;
		return true;
	}
	return false;
}
