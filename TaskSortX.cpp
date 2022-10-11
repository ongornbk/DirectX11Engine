#include "TaskSortX.h"
#include "Sorting.h"
#include <algorithm>

TaskSortX::TaskSortX(modern_array<class GameObject*>* const arr)
{
	m_arr = arr;
}

TaskSortX::~TaskSortX()
{
}

void TaskSortX::execute()
{
	std::_Sort_unchecked(m_arr->begin(), m_arr->end(), m_arr->size(), __sort__SortByX());
}
