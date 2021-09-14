#pragma once
#include "DeleteArrayTrash.h"

template<class T>
inline DeleteArrayTrash<T>::DeleteArrayTrash(modern_array<T>* data) : ITrash((void*)data)
{
}

template<class T>
inline DeleteArrayTrash<T>::~DeleteArrayTrash()
{
	if (ITrash::m_data)
	{
		for (T& ele : (*(class modern_array<T>*)ITrash::m_data))
		{
			if (ele)
			{
				delete ele;
				ele = nullptr;
			}
		}
		delete ITrash::m_data;
		ITrash::m_data = nullptr;
	}
}
