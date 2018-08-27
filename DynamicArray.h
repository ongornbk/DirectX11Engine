#pragma once
#include <mutex>
#include <future>
#include <atomic>
#include <stdlib.h>
#include <iterator>

#pragma region
class DynamicArray;

template<class Type>
struct MemberPtrBase {
	virtual ~MemberPtrBase() { }

	virtual Type get() const = 0;
	virtual MemberPtrBase & set(Type const &) = 0;
};

template<class Type, class RealType, class CommonType>
struct MemberPtr : MemberPtrBase<CommonType> {
public:
	MemberPtr(Class * object, RealType(Class::*member))
		: m_object(object), m_ptr(member)
	{ }

	CommonType get() const {
		return m_object->*m_ptr;
	}

	MemberPtr & set(CommonType const & val) {
		m_object->*m_ptr = val;
		return *this;
	}

	MemberPtr & operator=(RealType const & val) {
		return set(val);
	}

	operator CommonType() const {
		return get();
	}
private:
	Class * m_object;
	RealType(Class::*m_ptr);
};

template<class Type, class... Args>
struct MemberIterator {
public:
	using CommonType = class std::common_type<Args...>::type;
public:
	MemberIterator(Type & object, size_t idx, Args(Type::*...member))
		: m_object(obj), m_index(idx), m_members{ new MemberPtr<Class, Types, CommonType>(&obj, member)... }
	{ }

	MemberPtrBase<CommonType> & operator*() const {
		return *m_members[m_index];
	}

	bool operator==(MemberIterator const & it) const {
		return (&m_object == &it.m_object) && (m_index == it.m_index);
	}

	bool operator!=(MemberIterator const & it) const {
		return (&m_object != &it.m_object) || (m_index != it.m_index);
	}

	MemberIterator & operator++() {
		++m_index;
		return *this;
	}

#pragma endregion

template <class Type>
class DynamicArray<Type>
{
public:
	using iterator = MemberIterator<DynamicArray, Type>;

	DynamicArray();
	~DynamicArray();

	void   push_front(Type object);
	void   push_back(Type object);
	void   pop_front();
	void   pop_back();

	void   clear();
	void   reserve(uint32 size);
	void   reverse();
	void   sort(bool(*function)(Type));
	void   erase(uint32 element);
	Type   at(uint32 element);
	Type   front();
	Type   back();
	Type   replace(Type object);
	uint32 size();
	uint32 capacity();


private:
	T * m_data;

	uint32 m_size;
	uint32 m_capacity;
};

template<class Type>
inline DynamicArray<Type>::DynamicArray()
{
	m_size = 0;
	m_capacity = 4;
	m_data = (Type*)malloc(sizeof(Type)*m_capacity);
}

template<class Type>
inline DynamicArray<Type>::~DynamicArray()
{
	if (m_data)
	{
		free(m_data);
		m_data = NULL;
	}
}

template<class Type>
inline void DynamicArray<Type>::push_front(Type object)
{
	if (object)
	{
		if (m_size >= m_capacity)
		{
			m_capacity = 2 * (m_capacity + 1);
			m_data = (Type*)realloc(m_data, m_capacity * sizeof(Type));
		}
		memmove(m_data + 1, m_data, m_size * sizeof(Type));
		memcpy(m_data, &element, sizeof(Type));
		m_size++;
	}
	else
	{
		return;
	}
}

template<class Type>
inline void DynamicArray<Type>::push_back(Type object)
{
	if (element)
	{
		if (m_size >= m_capacity)
		{
			m_capacity = 2 * (m_capacity + 1);
			m_data = (Type*)realloc(m_data, m_capacity * sizeof(Type));
		}

		memcpy(m_data + m_size, &element, sizeof(Type));
		m_size++;
	}
	else
	{
		return;
	}
}

template<class Type>
inline void DynamicArray<Type>::pop_front()
{
	if (m_size)
	{
		memmove(m_data, m_data + 1, sizeof(Type)*m_size);
		m_size--;
	}
}

template<class Type>
inline void DynamicArray<Type>::pop_back()
{
	if (m_size)
	{
		m_size--;
	}
	else return;
}

template<class Type>
inline void DynamicArray<Type>::clear()
{
	if (m_data)
	{
		free(m_data);
		m_data = NULL;
		m_size = 0;
		m_capacity = 4;
		m_data = (Type*)malloc(sizeof(Type)*m_capacity);
	}
}

template<class Type>
inline void DynamicArray<Type>::reserve(uint32 size)
{
	if (size < m_capacity)
	{
		m_capacity = size + 1;
		m_data = (Type*)realloc(m_data, m_capacity * sizeof(Type));
	}
	else return;
}

template<class Type>
inline void DynamicArray<Type>::reverse()
{
	uint32 max = m_size - 1;
	Type temp;
	for (size_t i = 0; i < m_size / 2; ++i) {
		temp = m_data[i];
		m_data[i] = m_data[max - i];
		m_data[max - i] = temp;
	}
}

template<class Type>
inline void DynamicArray<Type>::sort(bool(*function)(Type))
{
	uint32 left = m_data;
	uint32 right = m_data + m_size;

		for (uint32 i = left + 1; i <= right; i++)
		{
			Type key = m_data[i];
			uint32 j = i - 1;


			while (function)
			{
				m_data[j + 1] = m_data[j];
				j = j - 1;
			}
			m_data[j + 1] = key;
		}

		return;
}

template<class Type>
inline void DynamicArray<Type>::erase(uint32 element)
{
	if (element < m_size)
	{
		memmove(m_data + element, m_data + element + 1, sizeof(Type)*(m_size - element - 1));
		m_size--;
	}
	else return;
}

template<class Type>
inline Type DynamicArray<Type>::at(uint32 element)
{
	if (element < m_size)
	{
		return *(m_data + element);
	}
	else
	{
		return nullptr;
	}
}

template<class Type>
inline Type DynamicArray<Type>::front()
{
	if (m_size)
	{
		return *(m_data);
	}
	else
	{
		return nullptr;
	}
}

template<class Type>
inline Type DynamicArray<Type>::back()
{
	if (m_size)
	{
		return *(m_data + (m_size - 1));
	}
	else
	{
		return nullptr;
	}
}
