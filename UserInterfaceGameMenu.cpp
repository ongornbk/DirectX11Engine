#include "UserInterfaceGameMenu.h"
#include "SettingsC.h"


UserInterfaceGameMenu::UserInterfaceGameMenu(Engine* engine, Shader* shader)
{
	m_engine = engine;
	m_cursor = new Sprite(UI_CURSOR_SIZE);
	m_cursor->Initialize(engine->GetGraphics()->GetDevice(), shader, L"ui_cursor", true);
	XMStoreFloat4x4(&m_cursorMatrix, XMMatrixIdentity());
	m_gameMenu = new Sprite(400.0f, 600.0f);
	m_gameMenu->Initialize(engine->GetGraphics()->GetDevice(), shader, L"ui_gameMenu", true);
	XMStoreFloat4x4(&m_gameMenuMatrix, XMMatrixIdentity());
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
	m_gameMenu->Render(deviceContext, m_gameMenuMatrix, viewMatrix, projectionMatrix);
	m_cursor->Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);
}

void UserInterfaceGameMenu::Update(XMVECTOR cameraPosition)
{
	m_input->GetMousePosition(xm, ym);
	XMStoreFloat4x4(&m_gameMenuMatrix, XMMatrixTranslation(cameraPosition.m128_f32[0], cameraPosition.m128_f32[1], cameraPosition.m128_f32[2]));
	xm -= (*(Settings::get()->RESOLUTION_X) / 2);
	ym -= (*(Settings::get()->RESOLUTION_Y) / 2);
	m_mousePosition.i = (SINDEX)(cameraPosition.m128_f32[0] + xm);
	m_mousePosition.j = (SINDEX)(cameraPosition.m128_f32[1] - ym);
	XMStoreFloat4x4(&m_cursorMatrix, XMMatrixTranslation(m_mousePosition.i, m_mousePosition.j, cameraPosition.m128_f32[2]));
}

void UserInterfaceGameMenu::GetMousePosition(int & x, int & y)
{
	x = (int)(m_mousePosition.i);
	y = (int)(m_mousePosition.j);
}