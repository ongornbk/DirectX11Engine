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

ThreadPool * ThreadPoolHandle::operator->()
{
	return pool;
}

void ThreadPoolHandle::wait()
{
	pool->wait();
}

ThreadPool::ThreadPool(size_t num_threads) :
 _taskNum(0) {
	_running.store(true);
	m_instance = this;
	auto thread_loop = [&](size_t id) {
		
		while (_running.load()) {
			unique_lock<mutex> lk(_mutex);
		//	_mutex.lock();
			if (!_taskQueue.empty()) {
				auto work = _taskQueue.front();
				_taskQueue.pop();
				lk.unlock();
				work();
				_taskNum--;
			}
			else
			{
				cv.wait(lk);
			}
		}
	};
	_threads.reserve(num_threads);
	for (size_t i = 0; i < num_threads; i++) {
		_threads.push_back(std::thread(thread_loop, i));
	}
}

ThreadPool::~ThreadPool() {
	_running.store(false);
	cv.notify_all();
	for (auto&& t : _threads) t.join();
}

void ThreadPool::push(tpTask work) {
	unique_lock<mutex> lk(_mutex);
	_taskQueue.push(work);
	_taskNum++;
	cv.notify_one();
}

void ThreadPool::clear() {
	std::queue<tpTask> empty;
	unique_lock<mutex> lk(_mutex);
	_taskNum -= _taskQueue.size();
	std::swap(_taskQueue, empty);
}

void ThreadPool::wait() {
	while (_taskNum.load() > 0) {
		std::this_thread::yield();
	}
}