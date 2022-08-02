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

	bool operator<(const struct modern_pack2& lhs) const
	{
		//return ((*first).get() < (*lhs.first).get()) || ((*second).get() < (*lhs.second).get());
		if (first->get() < lhs.first->get())
		{
			return true;
		}
		if (first->get() > lhs.first->get())
		{
			return false;
		}
		//if (second->get() < lhs.second->get())
		//{
		//	return modern_true;
		//}
		//if (second->get() > lhs.second->get())
		//{
		//	return modern_false;
		//}

		//return second->get() < lhs.second->get();

		return false;
	}

	modern_Boolean operator ==(const struct modern_pack2& lhs) const
	{
		return ((*first).get() == (*lhs.first).get()) && ((*second).get() == (*lhs.second).get());
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