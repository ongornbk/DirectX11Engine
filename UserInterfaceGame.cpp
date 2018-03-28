#include "UserInterfaceGame.h"
#include "SettingsC.h"

#define UI_CURSOR_SIZE 48.0f
#define UI_MUI_OFFSET 455.0f
#define UI_MUI_HEIGHT 175.0f
#define UI_CURSOR_ZERO_Z 0.0f

#pragma region

#pragma endregion

namespace
{
	ASINDEX2 m_mousePosition;
	Engine*  m_engine;
	Input*   m_input;

	static int xm, ym;
}

UserInterfaceGame::UserInterfaceGame(Engine* engine,Shader* shader)
{
	m_engine = engine;
	m_cursor = new Sprite(UI_CURSOR_SIZE);
	m_cursor->Initialize(engine->GetGraphics()->GetDevice(), shader, L"ui_cursor", true);
	XMStoreFloat4x4(&m_cursorMatrix, XMMatrixIdentity());
	m_ui = new Sprite((float)*(Settings::get()->RESOLUTION_X), 175.0f);
	m_ui->Initialize(engine->GetGraphics()->GetDevice(), shader, L"ui_game", true);
	XMStoreFloat4x4(&m_uiMatrix, XMMatrixIdentity());
	m_input = m_engine->GetInput();
}

void UserInterfaceGame::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
	m_ui->Render(deviceContext, m_uiMatrix, viewMatrix, projectionMatrix);
	m_cursor->Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);
}

void UserInterfaceGame::Update(XMVECTOR cameraPosition)
{
	m_input->GetMousePosition(xm, ym);
	XMStoreFloat4x4(&m_uiMatrix, XMMatrixTranslation(cameraPosition.m128_f32[0], cameraPosition.m128_f32[1] - UI_MUI_OFFSET,cameraPosition.m128_f32[2]));
	xm -= (*(Settings::get()->RESOLUTION_X)/2);
	ym -= (*(Settings::get()->RESOLUTION_Y)/2);
	m_mousePosition.i = (SINDEX)(cameraPosition.m128_f32[0] + xm);
	m_mousePosition.j = (SINDEX)(cameraPosition.m128_f32[1] - ym);
	XMStoreFloat4x4(&m_cursorMatrix, XMMatrixTranslation(m_mousePosition.i, m_mousePosition.j,cameraPosition.m128_f32[2]));
}


UserInterfaceGame::~UserInterfaceGame()
{
	if (m_cursor)
	{
		delete m_cursor;
		m_cursor = NULL;
	}
	if (m_ui)
	{
		delete m_ui;
		m_ui = NULL;
	}
}

void UserInterfaceGame::GetMousePosition(int & x,int & y)
{
	x =(int)m_mousePosition.i;
	y =(int)m_mousePosition.j;
}
