#include "UserInterfaceGame.h"
#include "SettingsC.h"
#include "LetterSprite.h"
#include "IPP.h"
#include "Defines.h"
#include <sstream>

#define UIG_HEIGHT 120.0F
#define TEXT_MARGIN_LEFT 20.0f
#define TEXT_MARGIN_TOP 20.0f
#define TEXT_FPS_MARGIN 25.0f

namespace
{
	static int m_fps = 0;
}

UserInterfaceGame::UserInterfaceGame(Engine* engine,Shader* shader)
{

	ID3D11Device* device = engine->GetGraphics()->GetDevice();
	ID3D11DeviceContext* deviceContext = engine->GetGraphics()->GetDeviceContext();
	float resolutionX = (float)*(Settings::get()->RESOLUTION_X);
	Font* font = Font::GetFontByName("ExocetLight");

	m_fpsText.Initialize(device, deviceContext, shader, font);
	m_fpsText.SetText("FPS ");
	m_mainText.Initialize(device, deviceContext, shader, font);
	m_mainText.SetText(string(GAME_NAME_VERSION));
	m_objectsText[0].Initialize(device, deviceContext, shader, font);
	m_objectsText[0].SetText("first square ");
	m_objectsText[1].Initialize(device, deviceContext, shader, font);
	m_objectsText[1].SetText("second square ");
	m_objectsText[2].Initialize(device, deviceContext, shader, font);
	m_objectsText[2].SetText("third square ");
	m_objectsText[3].Initialize(device, deviceContext, shader, font);
	m_objectsText[3].SetText("fourth square ");
	m_engine = engine;
	m_cursor = new Sprite(UI_CURSOR_SIZE);



	m_cursor->Initialize(device, shader, L"ui_cursor", true);
	XMStoreFloat4x4(&m_cursorMatrix, XMMatrixIdentity());
	m_ui = new Sprite(resolutionX, UIG_HEIGHT);
	m_ui->Initialize(device, shader, L"ui_game", true);
	XMStoreFloat4x4(&m_uiMatrix, XMMatrixIdentity());
	m_input = m_engine->GetInput();

	
}

void UserInterfaceGame::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
	m_ui->Render(deviceContext, m_uiMatrix, viewMatrix, projectionMatrix);
	m_fpsText.Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);
	m_mainText.Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);
	m_objectsText[0].Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);
	m_objectsText[1].Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);
	m_objectsText[2].Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);
	m_objectsText[3].Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);


	m_cursor->Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);

}

void UserInterfaceGame::Update(XMVECTOR cameraPosition)
{
	int xr = (*(Settings::get()->RESOLUTION_X)/2);
	int yr = (*(Settings::get()->RESOLUTION_Y)/2);
	m_input->GetMousePosition(xm, ym);
	XMStoreFloat4x4(&m_uiMatrix, XMMatrixTranslation(cameraPosition.m128_f32[0], cameraPosition.m128_f32[1] - UI_MUI_OFFSET,cameraPosition.m128_f32[2]));
	xm -= xr;
	ym -= yr;
	m_mousePosition.i = (SINDEX)(cameraPosition.m128_f32[0] + xm);
	m_mousePosition.j = (SINDEX)(cameraPosition.m128_f32[1] - ym);
	XMStoreFloat4x4(&m_cursorMatrix, XMMatrixTranslation(m_mousePosition.i, m_mousePosition.j,cameraPosition.m128_f32[2]));
	stringstream ssfps,ssobj[4];
	ssfps << m_fps;
	string fps = "FPS " + string(ssfps.str());
	m_fpsText.SetText(fps);
	__m128 ts = RendererManager::GetNumberOfObjectsX4();
	ssobj[0] << ts.m128_u32[0];
	string objn = "first " + string(ssobj[0].str());
	m_objectsText[0].SetText(objn);
	ssobj[1] << ts.m128_u32[1];
	 objn = "second " + string(ssobj[1].str());
	m_objectsText[1].SetText(objn);
	ssobj[2] << ts.m128_u32[2];
	objn = "third " + string(ssobj[2].str());
	m_objectsText[2].SetText(objn);
	ssobj[3] << ts.m128_u32[3];
	objn = "fourth " + string(ssobj[3].str());
	m_objectsText[3].SetText(objn);
	m_mainText.SetPosition(XMFLOAT3(cameraPosition.m128_f32[0] - (float)xr + TEXT_MARGIN_LEFT, cameraPosition.m128_f32[1] +(float)yr - TEXT_MARGIN_TOP, cameraPosition.m128_f32[2]));
	m_fpsText.SetPosition(XMFLOAT3(cameraPosition.m128_f32[0] - (float)xr + TEXT_MARGIN_LEFT, cameraPosition.m128_f32[1] + (float)yr - (TEXT_MARGIN_TOP+TEXT_FPS_MARGIN), cameraPosition.m128_f32[2]));
	m_objectsText[0].SetPosition(XMFLOAT3(cameraPosition.m128_f32[0] - (float)xr + TEXT_MARGIN_LEFT, cameraPosition.m128_f32[1] + (float)yr - (TEXT_MARGIN_TOP + (TEXT_FPS_MARGIN*3.0f)), cameraPosition.m128_f32[2]));
	m_objectsText[1].SetPosition(XMFLOAT3(cameraPosition.m128_f32[0] - (float)xr + TEXT_MARGIN_LEFT, cameraPosition.m128_f32[1] + (float)yr - (TEXT_MARGIN_TOP + (TEXT_FPS_MARGIN*4.0f)), cameraPosition.m128_f32[2]));
	m_objectsText[2].SetPosition(XMFLOAT3(cameraPosition.m128_f32[0] - (float)xr + TEXT_MARGIN_LEFT, cameraPosition.m128_f32[1] + (float)yr - (TEXT_MARGIN_TOP + (TEXT_FPS_MARGIN*5.0f)), cameraPosition.m128_f32[2]));
	m_objectsText[3].SetPosition(XMFLOAT3(cameraPosition.m128_f32[0] - (float)xr + TEXT_MARGIN_LEFT, cameraPosition.m128_f32[1] + (float)yr - (TEXT_MARGIN_TOP + (TEXT_FPS_MARGIN*6.0f)), cameraPosition.m128_f32[2]));
	m_fpsText.Update();
	m_mainText.Update();
	m_objectsText[0].Update();
	m_objectsText[1].Update();
	m_objectsText[2].Update();
	m_objectsText[3].Update();
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

void UserInterfaceGame::GetMousePosition(int16_t & x,int16_t & y)
{
	x =(m_mousePosition.i);
	y =(m_mousePosition.j);
}
