#pragma once
#include "ITrash.h"
#include "modern/modern_array.h"

template <class T>
class DeleteArrayTrash : public ITrash
{
	void* m_data;
public:
	DeleteArrayTrash() = delete;
	DeleteArrayTrash(modern_array<T>*& data);

	~DeleteArrayTrash();
};

#include "DeleteArrayTrash.inl"