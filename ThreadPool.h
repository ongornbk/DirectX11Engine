#pragma once
#include "Vector.h"
#include <algorithm>
#include <future>
#include <thread>
#include <atomic>
#include <mutex>
#include <queue>
#include <functional>
#include <condition_variable>


typedef std::function<void(void)> tpTask;

using std::atomic;
using std::mutex;
using std::condition_variable;
using std::unique_lock;
using std::vector;

class ThreadPool {
private:
	atomic<bool> _running;
	std::queue<tpTask> _taskQueue;
	condition_variable cv;
	atomic<size_t> _taskNum;
	mutex _mutex;
	vector<std::thread> _threads;
public:
	ThreadPool(const size_t num_threads = std::thread::hardware_concurrency());
	~ThreadPool();
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
