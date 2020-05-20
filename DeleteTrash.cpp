#include "DeleteTrash.h"

DeleteTrash::DeleteTrash(void* const data) : ITrash(data)
{

}

DeleteTrash::~DeleteTrash()
{
	if (m_data)
		delete m_data;
}