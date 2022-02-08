#pragma once
#include <cstdint>

struct modern_class;


class modern_handle
{
	volatile struct modern_class** m_object;
	volatile int64_t*      m_num;
	friend struct modern_class;

	modern_handle& operator=(modern_handle const&);
protected:

	//explicit modern_handle(struct modern_class* const obj);
	void make_handle(struct modern_class* const obj);
	void Release() const;
public:

	modern_handle();
	
	void make_handle(const class modern_handle& diff);
	~modern_handle();
	volatile struct modern_class* operator->();
	volatile struct modern_class* const get();
};

