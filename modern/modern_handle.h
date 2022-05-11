#pragma once
#include <cstdint>

struct modern_class;
class modern_class_view;


class modern_handle
{
	volatile struct modern_class** m_object;
	volatile int64_t*      m_num;
	friend struct modern_class;

	modern_handle& operator=(modern_handle const&);
	bool operator< (const modern_handle& rhs);
protected:

	//explicit modern_handle(struct modern_class* const obj);
	void make_handle(struct modern_class* const obj);
	void make_handle(volatile struct modern_class* const obj) volatile;
	void Release() const;
public:

	modern_handle();
	[[nodiscard]]modern_handle(const class modern_handle& diff);
	[[nodiscard]] modern_handle(class modern_class_view& view);
	

	void make_handle(const class modern_handle& diff);
	void make_handle(volatile class modern_handle& diff) volatile;
	~modern_handle();
	volatile struct modern_class* operator->();
	volatile struct modern_class* const get();

	void release();

	friend bool operator< (const modern_handle& lhs, const modern_handle& rhs);
};

bool operator< (const modern_handle& lhs, const modern_handle& rhs);