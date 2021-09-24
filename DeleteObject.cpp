#include "DeleteObject.h"
#include "RenderContainer.h"

DeleteObjectTrash::DeleteObjectTrash(void* const data) : ITrash(data)
{

}

DeleteObjectTrash::~DeleteObjectTrash()
{
	delete (class EObject*)m_data;
	m_data = nullptr;
}
