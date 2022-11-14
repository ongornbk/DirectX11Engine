#pragma once
#include "modern_handle.h"
#include "modern_unique.h"
#include "modern_class.h"
#include "modern_class_view.h"
#include <bitset>

struct modern_pack2
{
	union
	{
		struct
		{
			class modern_handle* first;
			class modern_handle* second;
		};
		__m128 m_data;
	};

	modern_pack2(modern_class_view A, modern_class_view B)
	{
		first = new modern_handle(A.GetHandle());
		second = new modern_handle(B.GetHandle());
	}

	modern_pack2(struct modern_pack2& other)
	{
		first = new modern_handle(*other.first);
		second = new modern_handle(*other.second);
	}

	modern_pack2(const struct modern_pack2& other)
	{
		first = new modern_handle(*other.first);
		second = new modern_handle(*other.second);
	}

	modern_pack2()
	{
		first = nullptr;
		second = nullptr;
	}

	~modern_pack2()
	{
		if (first)
		{
			delete first;
			delete second;
		}
	}

	struct modern_pack2& operator= (const struct modern_pack2& other)
	{
		if (this == &other)
			return *this;

		first->make_handle(*other.first);
		second->make_handle(*other.second);

		return *this;
	}
};

//struct modern_pack2_less_first : public std::binary_function<struct modern_pack2,struct  modern_pack2, bool> {
//	bool operator()(const modern_pack2& lhs, const modern_pack2& rhs) const
//	{
//		return lhs.first->get() < rhs.first->get();
//	}
//};

struct modern_pack2_less_second{
	bool operator()(const modern_pack2& lhs, const modern_pack2& rhs) const
	{
		return lhs.second->get() < rhs.second->get();
	}
};