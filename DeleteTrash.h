#pragma once
#include "ITrash.h"

class DeleteTrash : public ITrash
{
	void* m_data;
public:
	DeleteTrash() = delete;
	DeleteTrash(void* const data);

	~DeleteTrash();
};
