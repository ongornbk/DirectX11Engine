#pragma once
#include "modern_handle.h"
#include "modern_unique.h"
#include "modern_class.h"
#include "modern_class_view.h"

struct modern_pack4
{
	union
	{
		struct
		{
			class modern_handle* first;
			class modern_handle* second;
			class modern_handle* third;
			class modern_handle* fourth;
		};
		__m256 m_data;
	};

	modern_pack4(modern_class_view A, modern_class_view B, modern_class_view C, modern_class_view D)
	{
		first = new modern_handle(A.GetHandle());
		second = new modern_handle(B.GetHandle());
		third = new modern_handle(C.GetHandle());
		fourth = new modern_handle(D.GetHandle());
	}

	modern_pack4(modern_class_view A, modern_class_view B)
	{
		first = new modern_handle(A.GetHandle());
		second = new modern_handle(B.GetHandle());
		third = nullptr;
		fourth = nullptr;
	}

	modern_pack4(struct modern_pack4& other)
	{
		first = new modern_handle(*other.first);
		second = new modern_handle(*other.second);
		third = new modern_handle(*other.third);
		fourth = new modern_handle(*other.fourth);
	}

	modern_pack4(const struct modern_pack4& other)
	{
		first = new modern_handle(*other.first);
		second = new modern_handle(*other.second);
		third = new modern_handle(*other.third);
		fourth = new modern_handle(*other.fourth);
	}

	modern_pack4()
	{
		first =  nullptr;
		second = nullptr;
		third =  nullptr;
		fourth = nullptr;
	}

	~modern_pack4()
	{
		if (first)
		{
			delete first;
			delete second;
			delete third;
			delete fourth;
		}
	}

	modern_Boolean operator<(const struct modern_pack4& lhs) const
	{
		//return ((*first).get() < (*lhs.first).get()) || ((*second).get() < (*lhs.second).get() || ((*third).get() < (*lhs.third).get() || ((*fourth).get() < (*lhs.fourth).get());
		if (first->get() < lhs.first->get())
		{
			return modern_false;
		}
		if (first->get() > lhs.first->get())
		{
			return modern_true;
		}
		if (second->get() < lhs.second->get())
		{
			return modern_false;
		}
		if (second->get() > lhs.second->get())
		{
			return modern_true;
		}
	}

	modern_Boolean operator ==(const struct modern_pack4& lhs) const
	{
		return ((*first).get() == (*lhs.first).get()) && ((*second).get() == (*lhs.second).get());
	}

	struct modern_pack4& operator= (const struct modern_pack4& other)
	{
		if (this == &other)
			return *this;

		first->make_handle(*other.first);
		second->make_handle(*other.second);
		third->make_handle(*other.third);
		fourth->make_handle(*other.fourth);

		return *this;
	}
};