#pragma once
#include <cstdint>

struct modern_class;


class modern_handle
{
	volatile modern_class** m_object;
	volatile int64_t*      m_num;
	friend struct modern_class;
protected:


	void Release() const;
public:

	modern_handle(struct modern_class* const obj);
	modern_handle(class modern_handle& diff);
	~modern_handle();
	volatile modern_class* operator->();
	volatile modern_class* get();
};

