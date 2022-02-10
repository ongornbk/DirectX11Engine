#pragma once
#include "ITrash.h"

class EObject;

class DeleteObjectTrash : public ITrash
{
	class EObject* m_data;
public:
	DeleteObjectTrash() = delete;
	DeleteObjectTrash(class EObject* const data);

	~DeleteObjectTrash();
};
