#pragma once
#include <cstdint>
#include <functional>

struct modern_class;
class modern_class_view;


class modern_handle
{
	volatile struct modern_class** m_object;
	volatile int64_t*      m_num;
	friend struct modern_class;
	friend class modern_weak_handle;

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

class modern_weak_handle
{
	volatile struct modern_class** m_object;
	volatile int64_t* m_num;
public:
	modern_weak_handle();
	~modern_weak_handle();
	[[nodiscard]] modern_weak_handle(const class modern_handle& diff);
	volatile struct modern_class* const get();
	void make_weak_handle(const class modern_handle& diff);
	void make_weak_handle(volatile class modern_handle& diff) volatile;

	void make_weak_handle(const class modern_weak_handle& diff);
	void make_weak_handle(volatile class modern_weak_handle& diff) volatile;
};

bool operator< (const modern_handle& lhs, const modern_handle& rhs);

struct modern_weak_handle_less : public std::binary_function<class modern_weak_handle, class  modern_weak_handle, bool> {
	bool operator()( class modern_weak_handle& lhs, class modern_weak_handle& rhs) const
	{
		return lhs.get() < rhs.get();
	}
};

struct modern_handle_less : public std::binary_function<class modern_handle, class  modern_handle, bool> {
	bool operator()(class modern_handle* lhs, class modern_handle* rhs) const
	{
		return lhs->get() < rhs->get();
	}
};