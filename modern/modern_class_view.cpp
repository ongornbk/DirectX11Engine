#include "modern_class_view.h"
#include "modern_handle.h"
#include "modern_class.h"

modern_class_view::modern_class_view(struct modern_class* const modern) : m_view(modern)
{
}

modern_class_view::modern_class_view(volatile struct modern_class* const modern) : m_view((struct modern_class* const)modern)
{

}

const class modern_handle& modern_class_view::GetHandle()
{
	return m_view->m_object;
}

volatile class modern_handle& modern_class_view::GetHandle() volatile
{
	return m_view->m_object;
}
