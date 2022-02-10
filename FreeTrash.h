#pragma once
#include "ITrash.h"

class FreeTrash : public ITrash
{
	void* m_data;
public:
	FreeTrash() = delete;
	FreeTrash(void* const data);

	~FreeTrash();
};

