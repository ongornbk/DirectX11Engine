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



UserInterfaceGame::UserInterfaceGame(
	class Engine * const engine,
	class Shader * const shader
)
{
	struct ID3D11Device* device = engine->GetGraphics()->GetDevice();
	struct ID3D11DeviceContext* deviceContext = engine->GetGraphics()->GetDeviceContext();
	class TextFont* font = TextFont::GetFontByName("ExocetLight");

	assert(font);

	//m_fpsText.Initialize(device, deviceContext, shader, font,12.f);
	//m_fpsText.SetText(std::string("FPS "));
	//m_mainText.Initialize(device, deviceContext, shader, font,12.f);
	//m_mainText.SetText(string(GAME_NAME_VERSION));
	//m_cpuText.Initialize(device, deviceContext, shader, font,12.f);
	//m_cpuText.SetText(std::string("CPU "));

	m_gameChat = new GameChat();
	m_gameChat->SetGlobals(device, deviceContext, shader);
	m_gameChat->SetFont(font);
	m_gameChat->SetTextsLimit(5u);

	//for (uint32_t i = 0u; i < CPU_MED; i++)
	//{
	//	cput.push_back(0.0);
	//}
	m_engine = engine;
	m_cursor = new Sprite(UI_CURSOR_SIZE);

	m_cursor->Initialize(device, shader, L"ui_cursor", true);
	XMStoreFloat4x4(&m_cursorMatrix, XMMatrixIdentity());
	m_ui = new Sprite((float)Settings::GetResolutionX(), UIG_HEIGHT);
	m_ui->Initialize(device, shader, L"ui_game", true);
	XMStoreFloat4x4(&m_uiMatrix, XMMatrixIdentity());
	m_input = m_engine->GetInput();

	xm = 0;
	ym = 0;

	m_mousePosition.x = 0.f;
	m_mousePosition.y = 0.f;

}

void UserInterfaceGame::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
	//m_ui->Render(deviceContext, m_uiMatrix, viewMatrix, projectionMatrix);
	//m_fpsText.Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);
	//m_mainText.Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);
	//m_cpuText.Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);

	//m_gameChat->Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);

	m_cursor->Render(deviceContext, m_cursorMatrix, viewMatrix, projectionMatrix);

}

void UserInterfaceGame::Update(DirectX::XMVECTOR cameraPosition)
{
	const  int32 xr = ((Settings::GetResolutionX())/2);
	const  int32 yr = ((Settings::GetResolutionY())/2);
	m_input->GetMousePosition(xm, ym);
	XMStoreFloat4x4(&m_uiMatrix, XMMatrixTranslation(cameraPosition.m128_f32[0], cameraPosition.m128_f32[1] - UI_MUI_OFFSET,cameraPosition.m128_f32[2]));
	xm -= xr;
	ym -= yr;
	m_mousePosition = {
		(cameraPosition.m128_f32[0] + xm ),
		(cameraPosition.m128_f32[1] - ym )
	};
	XMStoreFloat4x4(&m_cursorMatrix, XMMatrixTranslation(m_mousePosition.x, m_mousePosition.y,cameraPosition.m128_f32[2]));
	//stringstream ssfps;
	//ssfps << m_fps;
	//string fps = "FPS " + string(ssfps.str());
	//m_fpsText.SetText(fps);
	//
	//double cputime = Get_CPU();
	//double med = 0.0;
	//
	//cput.pop_front();
	//cput.push_back(cputime);
	//
	//for (auto time : cput)
	//{
	//	med += time;
	//}
	//
	//med /= double(CPU_MED);
	//
	//std::stringstream ss;
	//float tempcpuA = ceilf((float)(100.0 * med));
	//if (isnan(tempcpuA))
	//	tempcpuA = 100.f;
	//ss << tempcpuA;
	//std::string cpu = "CPU " + string(ss.str());
	//m_cpuText.SetText(cpu);



	//std::vector<int64> ts = RendererManager::GetNumberOfObjectsVector();

	//for (uint32_t i = 0u; i < 16u; i++)
	//{
	//	stringstream ssobj;
	//	ssobj << ts[i];
	//	string objn = msq[i] + string(ssobj.str());
	//	m_objectsText[i]->SetText(objn);
	//	m_objectsText[i]->SetPosition(XMFLOAT3(cameraPosition.m128_f32[0] - (float)xr + TEXT_MARGIN_LEFT, cameraPosition.m128_f32[1] + (float)yr - (TEXT_MARGIN_TOP + (TEXT_FPS_MARGIN*(3.0f+float(i)))), cameraPosition.m128_f32[2]));
	//}
	
	//m_gameChat->SetTextPosition(XMFLOAT3( cameraPosition.m128_f32[0] - (float)xr + 30.0f,cameraPosition.m128_f32[1] + (float)yr - 700.0f ,cameraPosition.m128_f32[2]));

	//m_mainText.SetPosition(XMFLOAT3(cameraPosition.m128_f32[0] - (float)xr + TEXT_MARGIN_LEFT, cameraPosition.m128_f32[1] +(float)yr - TEXT_MARGIN_TOP, cameraPosition.m128_f32[2]));
	//m_fpsText.SetPosition(XMFLOAT3(cameraPosition.m128_f32[0] - (float)xr + TEXT_MARGIN_LEFT, cameraPosition.m128_f32[1] + (float)yr - (TEXT_MARGIN_TOP+TEXT_FPS_MARGIN), cameraPosition.m128_f32[2]));
	//m_cpuText.SetPosition(XMFLOAT3(cameraPosition.m128_f32[0] - (float)xr + TEXT_MARGIN_LEFT, cameraPosition.m128_f32[1] + (float)yr - (TEXT_MARGIN_TOP + TEXT_CPU_MARGIN), cameraPosition.m128_f32[2]));

	//m_gameChat->Update();
	//m_fpsText.Update();
	//m_mainText.Update();
	//m_cpuText.Update();
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

}

void UserInterfaceGame::SetFPS(const int32 fps) modern_except_state
{
	m_fps = fps;
}

void UserInterfaceGame::GetMousePosition(float & x, float& y)
{
	x = m_mousePosition.x;
	y = m_mousePosition.y;
}

GameChat * UserInterfaceGame::GetGameChat()
{
	if (m_gameChat)
	{
		return m_gameChat;
	}
	else return m_gameChat = new GameChat();
}
