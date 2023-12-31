#ifndef TIME_HPP_
#define TIME_HPP_

#include <string>
#include <chrono>

class Timer {
private:
	std::chrono::time_point<std::chrono::steady_clock> m_last;
	std::chrono::duration<double, std::milli> m_period;

public:
	Timer(std::chrono::duration<double> period);
	bool tick();
};

class Stopwatch {
private:
	std::string m_label;
	std::chrono::time_point<std::chrono::steady_clock> m_lap;
	int m_laps;
	double m_mean, m_var;

public:
	Stopwatch();
	Stopwatch(std::string label);
	void start();
	void lap();
	void stop();
};

#endif