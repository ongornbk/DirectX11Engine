#pragma once
#include "DeleteArrayTrash.h"

template<class T>
inline DeleteArrayTrash<T>::DeleteArrayTrash(modern_array<T>*& data) : m_data((void*)data)
{
}

template<class T>
inline DeleteArrayTrash<T>::~DeleteArrayTrash()
{
	class modern_array<T>* arr = (class modern_array<T>*)m_data;
	if (arr)
	{
		for (int32_t i = 0;i < arr->size();i++)
		{
			if ((*arr)[i])
			{
				delete (*arr)[i];
				(*arr)[i] = nullptr;
			}
		}
		delete arr;
		m_data = nullptr;
	}
}
