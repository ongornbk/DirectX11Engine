#pragma once
#include "modern/modern_thread_pool.h"
#include "modern/modern_mqueue.h"
#include "modern/modern_shared.h"
#include "ITask.h"

class MPManager
{
	MPManager() = delete;
public:
	class modern_thread_pool* m_pool;
	class modern_mqueue*      m_queue;

	class modern_mqueue_handle* m_tempHandle;//Not a real handle just guard

	MPManager(const size_t num_of_threads);
	~MPManager();

	static void Initialize(const size_t num_of_threads);
	static void Release();
	static class MPManager* const Get() modern_except_state;

	void begin_weak_pushing() modern_except_state;
	void weak_push(class ITask* const task);
	void push(class ITask* const task);
	void barrier() modern_except_state;
	void finalize_weak_pushing() modern_except_state;
	void increment() modern_except_state;
	void decrement() modern_except_state;
};





