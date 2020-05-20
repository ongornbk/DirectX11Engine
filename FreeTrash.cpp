#include "FreeTrash.h"
#include <cstdlib>

FreeTrash::FreeTrash(void* const data) : ITrash(data)
{

}

FreeTrash::~FreeTrash()
{
	if (m_data)
		free(m_data);
}