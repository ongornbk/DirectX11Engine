#include "DeleteTrash.h"

DeleteTrash::DeleteTrash(void* const data) : m_data(data)
{

}

DeleteTrash::~DeleteTrash()
{
	if (m_data)
		delete m_data;
	m_data = nullptr;
}