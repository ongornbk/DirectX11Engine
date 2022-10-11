#pragma once
#include "ITrash.h"

class GameObject;

class DeleteObjectTrash : public ITrash
{
	class GameObject* m_data;
public:
	DeleteObjectTrash() = delete;
	DeleteObjectTrash(class GameObject* const data);

	~DeleteObjectTrash();
};
