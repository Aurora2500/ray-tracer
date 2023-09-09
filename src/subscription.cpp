#include "subscription.hpp"

void Subscription::subscribe(std::function<void()> subscriber)
{
	m_subscribers.push_back(subscriber);
}

void Subscription::notify()
{
	for (auto& subscriber : m_subscribers) {
		subscriber();
	}
}

void Subscription::operator+=(std::function<void()> subscriber)
{
	subscribe(subscriber);
}