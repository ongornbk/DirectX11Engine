#pragma once
#include "modern/modern_thread_pool.h"
#include "modern/modern_mqueue.h"
#include "modern/modern_shared.h"
#include "modern/modern_task.h"

#include <folly/ProducerConsumerQueue.h>

class MPManager
{
	MPManager() = delete;
public:
	class modern_thread_pool* m_pool;
	struct folly::ProducerConsumerQueue<modern_task*>      m_queue;

	class modern_mqueue_handle* m_tempHandle;//Not a real handle just guard

	MPManager(const size_t num_of_threads);
	~MPManager();

	static void Initialize(const size_t num_of_threads);
	static void Release();
	static class MPManager* const Get() modern_except_state;

	void push(class modern_task* task);
	void barrier() modern_except_state;

};





