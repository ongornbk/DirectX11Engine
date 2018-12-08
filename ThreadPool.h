#pragma once
#include "Vector.h"
#include <algorithm>
#include <future>
#include <thread>
#include <atomic>
#include <mutex>
#include <queue>
#include <functional>


typedef std::function<void(void)> tpTask;

class ThreadPool {
private:
	bool _running;
	std::queue<tpTask> _taskQueue;
	std::atomic<size_t> _taskNum;
	std::mutex _mutex;
	std::vector<std::thread> _threads;
public:
	ThreadPool(size_t num_threads = std::thread::hardware_concurrency());
	virtual ~ThreadPool();
	void push(tpTask work);
	void clear();
	void wait();
};

struct ThreadPoolHandle
{
	ThreadPoolHandle();
	~ThreadPoolHandle();
	ThreadPool* pool;

	void operator << (tpTask task);
};
