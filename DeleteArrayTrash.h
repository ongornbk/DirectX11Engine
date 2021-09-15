#pragma once
#include "ITrash.h"
#include "modern/modern_array.h"

template <class T>
class DeleteArrayTrash : public ITrash
{
public:
	DeleteArrayTrash() = delete;
	DeleteArrayTrash(modern_array<T>*& data);

	~DeleteArrayTrash();
};

#include "DeleteArrayTrash.inl"