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

using std::atomic;
using std::mutex;

class ThreadPool {
private:
	bool _running;
	std::queue<tpTask> _taskQueue;
	atomic<size_t> _taskNum;
	mutex _mutex;
	Vector<std::thread*> _threads;
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


	void operator << (tpTask task);
	ThreadPool* operator ->();
	void wait();

	private:

	ThreadPool* pool;
};
