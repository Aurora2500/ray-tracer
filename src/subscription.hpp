#pragma once

#include <vector>
#include <functional>

class Subscription {
private:
	std::vector<std::function<void()>> m_subscribers;

public:
	Subscription() = default;

	void subscribe(std::function<void()> subscriber);
	void notify();

	void operator+=(std::function<void()> subscriber);
};