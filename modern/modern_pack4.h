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
			class modern_unique<class modern_handle> first;
			class modern_unique<class modern_handle> second;
			class modern_unique<class modern_handle> third;
			class modern_unique<class modern_handle> fourth;
		};
		class modern_unique<class modern_handle> m_data[4];
	};

	modern_pack4(modern_class_view A, modern_class_view B, modern_class_view C, modern_class_view D)
	{
		first.make_unique(new modern_handle(A.GetHandle()));
		second.make_unique(new modern_handle(B.GetHandle()));
		third.make_unique(new modern_handle(C.GetHandle()));
		fourth.make_unique(new modern_handle(D.GetHandle()));
	}

	modern_pack4(modern_class_view A, modern_class_view B)
	{
		first.make_unique(new modern_handle(A.GetHandle()));
		second.make_unique(new modern_handle(B.GetHandle()));
		third.make_unique(new modern_handle());
		fourth.make_unique(new modern_handle());
	}

	modern_pack4(struct modern_pack4& other)
	{
		first.make_unique(new modern_handle(*other.first));
		second.make_unique(new modern_handle(*other.second));
		third.make_unique(new modern_handle(*other.third));
		fourth.make_unique(new modern_handle(*other.fourth));
	}

	modern_pack4()
	{

	}

	~modern_pack4()
	{

	}

	modern_Boolean operator<(const modern_pack4& lhs) const
	{
		return ((*first).get() < (*lhs.first).get()) || ((*second).get() < (*lhs.second).get());
	}

	modern_Boolean operator ==(const modern_pack4& lhs) const
	{
		return ((*first).get() == (*lhs.first).get()) && ((*second).get() == (*lhs.second).get());
	}
};