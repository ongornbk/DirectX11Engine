#pragma once
#include "ITrash.h"

class FreeTrash : public ITrash
{
public:
	FreeTrash() = delete;
	FreeTrash(void* const data);

	~FreeTrash();
};

