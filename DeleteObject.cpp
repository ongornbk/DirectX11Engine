#include "DeleteObject.h"
#include "RenderContainer.h"

DeleteObjectTrash::DeleteObjectTrash(class EObject* const data) : m_data(data)
{

}

DeleteObjectTrash::~DeleteObjectTrash()
{
	modern_guard g(m_data);
	delete m_data;
	m_data = nullptr;
}
