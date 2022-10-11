#include "DeleteObject.h"
#include "GameObject.h"

DeleteObjectTrash::DeleteObjectTrash(class GameObject* const data) : m_data(data)
{

}

DeleteObjectTrash::~DeleteObjectTrash()
{
	modern_guard g(m_data);
	delete m_data;
	m_data = nullptr;
}
