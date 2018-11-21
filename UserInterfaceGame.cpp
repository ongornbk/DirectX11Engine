#include "UserInterfaceGame.h"
#include "SettingsC.h"
#include "LetterSprite.h"
#include "IPP.h"
#include "Defines.h"
#include "GlobalVariables.h"
#include "CPU.h"
#include <sstream>
#include <list>

#define UIG_HEIGHT 120.0F
#define TEXT_MARGIN_LEFT 20.0f
#define TEXT_MARGIN_TOP 20.0f
#define TEXT_FPS_MARGIN 25.0f
#define TEXT_CPU_MARGIN 50.0f
#define CPU_MED 100

namespace
{
	static int m_fps = 0;
	static GameChat* m_gameChat = nullptr;
	static std::list<double> cput;
}



UserInterfaceGame::UserInterfaceGame(Engine* engine,Shader* shader)
{
	ID3D11Device* device = engine->GetGraphics()->GetDevice();
	ID3D11DeviceContext* deviceContext = engine->GetGraphics()->GetDeviceContext();
	Font* font = Font::GetFontByName("ExocetLight");

	m_fpsText.Initialize(device, deviceContext, shader, font);
	m_fpsText.SetText("FPS ");
	m_mainText.Initialize(device, deviceContext, shader, font);
	m_mainText.SetText(string(GAME_NAME_VERSION));
	m_cpuText.Initialize(device, deviceContext, shader, font);
	m_cpuText.SetText("CPU ");

	m_gameChat = new GameChat();
	m_gameChat->SetGlobals(device, deviceContext, shader);
	m_gameChat->SetFont(font);
	m_gameChat->SetTextsLimit(5u);

	for (uint32_t i = 0u; i < CPU_MED; i++)
	{
		cput.push_back(0.0);
	}
	m_engine = engine;
	m_cursor = new Sprite(UI_CURSOR_SIZE);

	m_cursor->Initialize(device, shader, L"ui_cursor", true);
	XMStoreFloat4x4(&m_cursorMatrix, XMMatrixIdentity());
	m_ui = new Sprite(Settings::GetResolutionX(), UIG_HEIGHT);
	m_ui->Initialize(device, shader, L"ui_game", true);
	XMStoreFloat4x4(&m_uiMatrix, XMMatrixIdentity());
	m_input = m_engine->GetInput();

}

void UserInterfaceGame::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
	m_ui->Render(deviceContext, m_uiMatrix, viewMatrix, projectionMatrix);
	m_fpsText.Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);
	m_mainText.Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);
	m_cpuText.Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);

	m_gameChat->Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);

	m_cursor->Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);

}

void UserInterfaceGame::Update(XMVECTOR cameraPosition)
{
	int xr = ((Settings::GetResolutionX())/2);
	int yr = ((Settings::GetResolutionY())/2);
	m_input->GetMousePosition(xm, ym);
	XMStoreFloat4x4(&m_uiMatrix, XMMatrixTranslation(cameraPosition.m128_f32[0], cameraPosition.m128_f32[1] - UI_MUI_OFFSET,cameraPosition.m128_f32[2]));
	xm -= xr;
	ym -= yr;
	m_mousePosition.i = (SINDEX)(cameraPosition.m128_f32[0] + xm);
	m_mousePosition.j = (SINDEX)(cameraPosition.m128_f32[1] - ym);
	XMStoreFloat4x4(&m_cursorMatrix, XMMatrixTranslation(m_mousePosition.i, m_mousePosition.j,cameraPosition.m128_f32[2]));
	stringstream ssfps;
	ssfps << m_fps;
	string fps = "FPS " + string(ssfps.str());
	m_fpsText.SetText(fps);

	double cputime = Get_CPU();
	double med = 0.0;

	cput.pop_front();
	cput.push_back(cputime);

	for (auto time : cput)
	{
		med += time;
	}

	med /= double(CPU_MED);

	std::stringstream ss;
	ss << ceilf(med*100);
	std::string cpu = "CPU " + string(ss.str());
	m_cpuText.SetText(cpu);



	std::vector<uint32_t> ts = RendererManager::GetNumberOfObjectsVector();

	//for (uint32_t i = 0u; i < 16u; i++)
	//{
	//	stringstream ssobj;
	//	ssobj << ts[i];
	//	string objn = msq[i] + string(ssobj.str());
	//	m_objectsText[i]->SetText(objn);
	//	m_objectsText[i]->SetPosition(XMFLOAT3(cameraPosition.m128_f32[0] - (float)xr + TEXT_MARGIN_LEFT, cameraPosition.m128_f32[1] + (float)yr - (TEXT_MARGIN_TOP + (TEXT_FPS_MARGIN*(3.0f+float(i)))), cameraPosition.m128_f32[2]));
	//}
	
	m_gameChat->SetTextPosition(XMFLOAT3( cameraPosition.m128_f32[0] - (float)xr + 30.0f,cameraPosition.m128_f32[1] + (float)yr - 700.0f ,cameraPosition.m128_f32[2]));

	m_mainText.SetPosition(XMFLOAT3(cameraPosition.m128_f32[0] - (float)xr + TEXT_MARGIN_LEFT, cameraPosition.m128_f32[1] +(float)yr - TEXT_MARGIN_TOP, cameraPosition.m128_f32[2]));
	m_fpsText.SetPosition(XMFLOAT3(cameraPosition.m128_f32[0] - (float)xr + TEXT_MARGIN_LEFT, cameraPosition.m128_f32[1] + (float)yr - (TEXT_MARGIN_TOP+TEXT_FPS_MARGIN), cameraPosition.m128_f32[2]));
	m_cpuText.SetPosition(XMFLOAT3(cameraPosition.m128_f32[0] - (float)xr + TEXT_MARGIN_LEFT, cameraPosition.m128_f32[1] + (float)yr - (TEXT_MARGIN_TOP + TEXT_CPU_MARGIN), cameraPosition.m128_f32[2]));

	m_gameChat->Update();
	m_fpsText.Update();
	m_mainText.Update();
	m_cpuText.Update();
	//for (uint32_t i = 0u; i < 16u; i++)
	//{
	//	m_objectsText[i]->Update();
	//}
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
	if (m_gameChat)
	{
		delete m_gameChat;
		m_gameChat = nullptr;
	}
	//for (auto && text : m_objectsText)
	//{
	//	if (text)
	//	{
	//		delete text;
	//		text = nullptr;
	//	}
	//}
	//m_objectsText.clear();
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

GameChat * UserInterfaceGame::GetGameChat()
{
	if (m_gameChat)
	{
		return m_gameChat;
	}
	else return m_gameChat = new GameChat();
}
