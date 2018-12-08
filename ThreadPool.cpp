#include "ThreadPool.h"

namespace
{
	static ThreadPool* m_instance = nullptr;
}

ThreadPoolHandle::ThreadPoolHandle()
{
	pool = m_instance;
}

ThreadPoolHandle::~ThreadPoolHandle()
{
	pool->wait();
}

void ThreadPoolHandle::operator<<(tpTask task)
{
	pool->push(task);
}

ThreadPool::ThreadPool(size_t num_threads) :
	_running(true), _taskNum(0) {
	m_instance = this;
	auto thread_loop = [&](size_t id) {
		while (_running) {
			_mutex.lock();
			if (!_taskQueue.empty()) {
				auto work = _taskQueue.front();
				_taskQueue.pop();
				_mutex.unlock();
				work();
				_taskNum--;
			}
			else {
				_mutex.unlock();
				std::this_thread::yield();
			}
		}
	};
	_threads.reserve(num_threads);
	for (size_t i = 0; i < num_threads; i++) {
		_threads.push_back(std::thread(thread_loop, i));
	}
}

ThreadPool::~ThreadPool() {
	_running = false;
	for (std::thread& t : _threads) {
		t.join();
	}
}

void ThreadPool::push(tpTask work) {
	_mutex.lock();
	_taskQueue.push(work);
	_taskNum++;
	_mutex.unlock();
}

void ThreadPool::clear() {
	std::queue<tpTask> empty;
	_mutex.lock();
	_taskNum -= _taskQueue.size();
	std::swap(_taskQueue, empty);
	_mutex.unlock();
}

void ThreadPool::wait() {
	while (_taskNum.load() > 0) {
		std::this_thread::yield();
	}
}