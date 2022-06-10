#pragma once
#include "modern_handle.h"
#include "modern_unique.h"
#include "modern_class.h"
#include "modern_class_view.h"

struct modern_pack2
{
	union
	{
		struct
		{
			class modern_unique<class modern_handle> first;
			class modern_unique<class modern_handle> second;
		};
		class modern_unique<class modern_handle> m_data[2];
	};

	modern_pack2(modern_class_view A, modern_class_view B)
	{
		first.make_unique(new modern_handle(A.GetHandle()));
		second.make_unique(new modern_handle(B.GetHandle()));
	}

	modern_pack2(struct modern_pack2& other)
	{
		first.make_unique(new modern_handle(*other.first));
		second.make_unique(new modern_handle(*other.second));
	}

	modern_pack2()
	{

	}

	~modern_pack2()
	{

	}

	modern_Boolean operator<(const struct modern_pack2& lhs) const
	{
		return ((*first).get() < (*lhs.first).get()) || ((*second).get() < (*lhs.second).get());
	}

	modern_Boolean operator ==(const struct modern_pack2& lhs) const
	{
		return ((*first).get() == (*lhs.first).get()) && ((*second).get() == (*lhs.second).get());
	}

	struct modern_pack2& operator= (const struct modern_pack2& other)
	{
		if (this == &other)
			return *this;
	
		first.make_unique(new modern_handle(*other.first));
		second.make_unique(new modern_handle(*other.second));
	
		return *this;
	}
};