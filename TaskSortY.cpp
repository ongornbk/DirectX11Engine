#include "TaskSortY.h"
#include "Sorting.h"
#include <algorithm>

TaskSortY::TaskSortY(modern_array<class GameObject*>* const arr)
{
	m_arr = arr;
}

TaskSortY::~TaskSortY()
{
}

void TaskSortY::execute()
{
	std::_Sort_unchecked(m_arr->begin(), m_arr->end(), m_arr->size(), __sort__SortByY());
}
