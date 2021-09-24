#pragma once
#include "ITrash.h"

class DeleteObjectTrash : public ITrash
{
public:
	DeleteObjectTrash() = delete;
	DeleteObjectTrash(void* const data);

	~DeleteObjectTrash();
};
