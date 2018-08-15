#include "UserInterfaceGame.h"
#include "SettingsC.h"
#include "LetterSprite.h"
#include "Onion.h"
#include <sstream>

#define UIG_HEIGHT 175.0F

namespace
{
	static int m_fps = 0;
}

UserInterfaceGame::UserInterfaceGame(Engine* engine,Shader* shader)
{
	m_fpsText.SetText("");
	m_engine = engine;
	m_cursor = new Sprite(UI_CURSOR_SIZE);

	ID3D11Device* device = engine->GetGraphics()->GetDevice();
	ID3D11DeviceContext* deviceContext = engine->GetGraphics()->GetDeviceContext();
	float resolutionX = (float)*(Settings::get()->RESOLUTION_X);
	Font* font = Font::GetFontByName("ExocetLight");

	m_cursor->Initialize(device, shader, L"ui_cursor", true);
	XMStoreFloat4x4(&m_cursorMatrix, XMMatrixIdentity());
	m_ui = new Sprite(resolutionX, UIG_HEIGHT);
	m_ui->Initialize(device, shader, L"ui_game", true);
	XMStoreFloat4x4(&m_uiMatrix, XMMatrixIdentity());
	m_input = m_engine->GetInput();
	m_fpsText.Initialize(device, deviceContext, shader, font);
	
}

void UserInterfaceGame::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
	m_ui->Render(deviceContext, m_uiMatrix, viewMatrix, projectionMatrix);
	m_cursor->Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);
	m_fpsText.Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);
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
	stringstream ss;
	ss << m_fps;
	string sss = ss.str();
	string fps = "FPS : " + string(ss.str());
	m_fpsText.SetText(fps);
	m_fpsText.SetPosition(XMFLOAT3(cameraPosition.m128_f32[0] + xm, cameraPosition.m128_f32[1] - ym, cameraPosition.m128_f32[2]));
	m_fpsText.Update();
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

void UserInterfaceGame::SetFPS(int fps)
{
	m_fps = fps;
}

void UserInterfaceGame::GetMousePosition(int & x,int & y)
{
	x =(int)(m_mousePosition.i);
	y =(int)(m_mousePosition.j);
}
