#pragma once
#include "ITrash.h"

class DeleteTrash : public ITrash
{
public:
	DeleteTrash() = delete;
	DeleteTrash(void* const data);

	~DeleteTrash();
};
