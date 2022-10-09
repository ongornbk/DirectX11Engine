#include "TaskUpdateInterface_v4.h"
#include "modern/modern_guard.h"
#include "Text.h"
#include "Camera.h"

TaskUpdateInterface_v4::TaskUpdateInterface_v4(const modern_handle& text)
{
	m_text.make_handle(text);
}

TaskUpdateInterface_v4::~TaskUpdateInterface_v4()
{
}

void TaskUpdateInterface_v4::execute()
{
	class Text* const A = (class Text* const)m_text.get();
	if (A)
	{
		modern_guard g(A);
		A->SetPosition(Camera::GetCurrentCamera()->GetPosition());
		A->Update();
	}
}
