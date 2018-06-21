#include "UserInterfaceGameMenu.h"



UserInterfaceGameMenu::UserInterfaceGameMenu(Engine* engine, Shader* shader)
{
	m_engine = engine;
	m_cursor = new Sprite(UI_CURSOR_SIZE);
	m_cursor->Initialize(engine->GetGraphics()->GetDevice(), shader, L"ui_cursor", true);
	XMStoreFloat4x4(&m_cursorMatrix, XMMatrixIdentity());
	m_input = m_engine->GetInput();
}


UserInterfaceGameMenu::~UserInterfaceGameMenu()
{
	if (m_cursor)
	{
		delete m_cursor;
		m_cursor = NULL;
	}
}

void UserInterfaceGameMenu::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
	m_cursor->Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);
}

void UserInterfaceGameMenu::Update(XMVECTOR cameraPosition)
{
	m_input->GetMousePosition(xm, ym);
	m_mousePosition.i = (SINDEX)(cameraPosition.m128_f32[0] + xm);
	m_mousePosition.j = (SINDEX)(cameraPosition.m128_f32[1] - ym);
	XMStoreFloat4x4(&m_cursorMatrix, XMMatrixTranslation(m_mousePosition.i, m_mousePosition.j, cameraPosition.m128_f32[2]));
}

void UserInterfaceGameMenu::GetMousePosition(int & x, int & y)
{
	x = (int)(m_mousePosition.i);
	y = (int)(m_mousePosition.j);
}
