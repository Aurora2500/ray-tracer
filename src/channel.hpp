#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <deque>
#include <atomic>
#include <optional>

template <typename T> class Sender;
template <typename T> class Receiver;

template <typename T>
class Channel {
private:
	std::mutex m_mutex;
	std::condition_variable m_available;
	std::atomic_uint32_t senders;

	std::deque<T> m_queue;
	friend class Sender<T>;
	friend class Receiver<T>;
};

template <typename T>
class Sender {
private:
	std::shared_ptr<Channel<T>> m_channel;
public:
	Sender() = default;
	Sender(std::shared_ptr<Channel<T>> channel)
		: m_channel(channel)
	{
		m_channel->senders.fetch_add(1);
	}
	~Sender() {
		if(!m_channel) {
			return;
		}
		auto last = m_channel->senders.fetch_sub(1);
		if (last == 1) {
			// notify all the receivers that there will be no more data
			m_channel->m_available.notify_all();
		}
	}

	void send(T value) {
		std::unique_lock<std::mutex> lock(m_channel->m_mutex);
		m_channel->m_queue.push_back(value);
		lock.unlock();
		m_channel->m_available.notify_one();
	}
};

template <typename T>
class Receiver {
private:
	std::shared_ptr<Channel<T>> m_channel;
public:
	Receiver() = default;
	Receiver(std::shared_ptr<Channel<T>> channel)
		: m_channel(channel)
	{
	}
	Receiver(const Receiver<T>& other)
		: m_channel(other.m_channel)
	{
	}

	std::optional<T> receive() {
		std::unique_lock<std::mutex> lock(m_channel->m_mutex);
		// wait for there to either be data or for the senders to be done
		uint32_t senders;
		while(m_channel->m_queue.empty() && (senders = m_channel->senders.load()) > 0) {
			m_channel->m_available.wait(lock);
		}
		// m_channel->m_available.wait(lock, [this] { return !m_channel->m_queue.empty(); });
		if (senders == 0 && m_channel->m_queue.empty()) {
			// there are no more senders and the queue is empty, so return none
			return std::nullopt;
		} else {
			// there is data, so return it
			T value = m_channel->m_queue.front();
			m_channel->m_queue.pop_front();
			return value;
		}
	}
};

template <typename T>
struct SenderReceiver {
	Sender<T> sender;
	Receiver<T> receiver;
};

template <typename T>
SenderReceiver<T> channel() {
	std::shared_ptr<Channel<T>> channel = std::make_shared<Channel<T>>();
	return SenderReceiver<T> {
		Sender<T>(channel),
		Receiver<T>(channel)
	};
}