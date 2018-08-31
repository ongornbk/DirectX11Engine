
#include "Engine.h"
#include "Onion.h"
#include "SettingsC.h"
#include "LUAManager.h"
#include "CALLBACK.cpp"
#include "S_ModelPaths.h"
#include "Font.h"
#include <map>
#include <streambuf>
#include <fstream>
#include <istream>
#include <sstream>
#include <stack>

using namespace Onion;

Engine* Engine::m_instance = NULL;

static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);



namespace
{

	static Sound*                  m_playingMusic = nullptr;



}


Engine::~Engine(void)
{
	if (m_graphics)
	{
		delete m_graphics;
		m_graphics = NULL;
	}
	if (m_rendererManager)
	{
		delete m_rendererManager;
		m_rendererManager = NULL;
	}
	if (m_camera)
	{
		delete m_camera;
		m_camera = NULL;
	}
	if (m_resourceManager)
	{
		delete m_resourceManager;
		m_resourceManager = NULL;
	}
	if (m_input)
	{
		delete m_input;
		m_input = NULL;
	}
	if (m_global)
	{
		delete m_global;
		m_global = NULL;
	}
	if (m_gameComponent)
	{
	//	delete m_gameComponent;
		m_gameComponent = NULL;
	}
	Font::ReleaseFonts();
	lua::Close();
}

Engine::Engine(void)
{
#pragma region
	m_gamePaused      = FALSE;
	m_graphics        = NULL;
	m_rendererManager = NULL;
	m_camera          = NULL;
	m_resourceManager = NULL;
	m_input           = NULL;
	m_gameComponent   = NULL;
	m_global          = NULL;
	m_framework       = NULL;
	m_lua             = NULL;
#pragma endregion
}

bool Engine::InitializeGraphics(HWND hwnd)
{
	m_graphics = new Graphics();
	return (m_graphics->InitializeDX(hwnd)&&m_graphics->InitializeVulcan(hwnd));
}



bool Engine::Initialize(HINSTANCE hInstance, HWND hwnd,FrameWork* framework)
{
#pragma region


#pragma endregion
#pragma region
#define LOADSHADER  m_resourceManager->LoadShaderResource(hwnd, 
#define END );
#pragma endregion
	//NEWS
	m_global = new Global();
	m_camera = new Camera();
	m_resourceManager = ResourceManager::GetInstance();
	//LUA CALLBACK
	lua_callback::Initialize(this);
	lua_callback::SetResourceManager(m_resourceManager);
	lua_callback::SetCamera(m_camera);
	//RESOURCE MANAGER
	rm::SetDevice(m_graphics->GetDevice());
	//LUA
	lua::Open();
	lua_callback::RegisterFunctions();

	//LUA EXECUTE

	lua::Execute(lua::LUA_LOCATION_ENGINE_INITIALIZATION);

	// END LUA EXECUTE

#pragma region
	LOADSHADER  L"../Shaders/texture.fx"                            END //HANDLED
	LOADSHADER  L"../Shaders/tile.fx"                               END //HANDLED
	TextureShader* shader = GETSHADER "texture.fx"                  END //HANDLED
#pragma endregion

	
	m_input = new Input();
	m_input->Initialize(hInstance, hwnd, (*(Settings::get()->RESOLUTION_X)), (*(Settings::get()->RESOLUTION_Y)));
	lua_callback::SetInput(m_input);
//	InitializeTemplates();
	m_rendererManager = new RendererManager(this, shader);
	lua_callback::SetRendererManager(m_rendererManager);
	
	m_cameraControl.SetCurrentCamera(m_camera);
	m_graphics->Initialize();

	lua_callback::InitializeGraphics();

	

	if(m_gameComponent!=NULL)
	{
		if (!m_gameComponent->Initialize())
		{
			return false;
		}
	}

	

	else
	{
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Engine : No Game Component" << endl;
	}
	
	


	return true;
}

namespace
{
	clock_t deltaTime = 0;
	unsigned int frames = 0;
	double  frameRate = 30;
	double  averageFrameTimeMilliseconds = 33.333;

	extern "C"
	{
		double clockToMilliseconds(clock_t ticks) _NOEXCEPT {
			// units/(units/time) => time (seconds) * 1000 = milliseconds
			return (ticks / (double)CLOCKS_PER_SEC)*1000.0;
		}
	}
}

void Engine::Run()
{
	clock_t beginFrame = clock();
	Update();
	Render();
	clock_t endFrame = clock();

	deltaTime += endFrame - beginFrame;
	frames++;

	if (clockToMilliseconds(deltaTime)>1000.0) {
		frameRate = (double)frames*0.5 + frameRate * 0.5;
		frames = 0;
		deltaTime -= CLOCKS_PER_SEC;
		averageFrameTimeMilliseconds = 1000.0 / (frameRate == 0 ? 0.001 : frameRate);

		int fps = (int)(1000 / averageFrameTimeMilliseconds);

		UserInterfaceGame::SetFPS(fps);

	}
}

void Engine::Release()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

void Engine::SetGameComponent(GameComponent * gameComponent)
{
	m_gameComponent = gameComponent;
}

void Engine::PauseGame()
{
	m_gamePaused = true;
}

void Engine::ResumeGame()
{
	m_gamePaused = false;
}

Sound * Engine::CreateSound(WCHAR* name)
{
	wstring tmp0 = wstring(name);
	string  tmp1 = string(tmp0.begin(), tmp0.end());
	return m_resourceManager->GetSoundByName((char*)tmp1.c_str());
}

Sound * Engine::CreateSound(WCHAR* name, bool looping)
{
	//Sound* sound = new Sound(name);
	wstring tmp0 = wstring(name);
	string  tmp1 = string(tmp0.begin(), tmp0.end());
	Sound* sound = m_resourceManager->GetSoundByName((char*)tmp1.c_str());
	sound->SetLooping(looping);
	return sound;
}

Sound * Engine::CreateSound(WCHAR* name, float volume)
{
	Sound* sound = new Sound(name);
	wstring tmp0 = wstring(name);
	string  tmp1 = string(tmp0.begin(), tmp0.end());
	sound = m_resourceManager->GetSoundByName((char*)tmp1.c_str());
	sound->SetVolume(volume);
	return sound;
}

Sound * Engine::CreateSound(WCHAR* name, float volume, bool looping)
{

	wstring tmp0 = wstring(name);
	string  tmp1 = string(tmp0.begin(), tmp0.end());
	Sound* sound = m_resourceManager->GetSoundByName((char*)tmp1.c_str());
	//MessageBox(NULL, (char*)tmp1.c_str(), NULL, NULL);
	sound->SetVolume(volume);
	sound->SetLooping(looping);
	return sound;
}

Sound * Engine::CreateSound(string name, float volume, bool looping)
{
	Sound* sound = m_resourceManager->GetSoundByName((char*)name.c_str());
	sound->SetVolume(volume);
	sound->SetLooping(looping);
	return sound;
}

void Engine::AddMusicSound(string name, float volume,bool looping)
{
	m_canals.__AddSound(CanalType::MUSIC, name, CreateSound(name, volume, looping));
}

void Engine::AddModelPaths(string name)
{
#pragma region
#pragma warning(disable : 4996)
	using std::getline;
	using std::istringstream;
	using std::stack;
#pragma endregion
	istringstream ss(name.c_str());
	string token;
	while (getline(ss, token, '/')) { ;; }
	wchar_t* wide_string = new wchar_t[name.length() + 1];
	wstring ws = std::wstring(name.begin(), name.end()).c_str();
	wcscpy(wide_string, ws.c_str());
	S_ModelPaths::AddModelPaths(token, wide_string);
	delete wide_string;
}

void Engine::AddFont(string filename, float width, float height)
{
	Font::LoadFontFromFile(filename, width, height);
}

void Engine::PlayMusic(WCHAR * music)
{
	wstring tmp0 = wstring(music);
	string  tmp1 = string(tmp0.begin(), tmp0.end());
	Sound* __music = m_canals.__GetSound(tmp1);
	if (m_playingMusic)
	{
		m_playingMusic->Stop();
	}
	m_playingMusic = __music;
	__music->Play();
}

CameraControl * Engine::GetCameraControl()
{
	return &m_cameraControl;
}

FrameWork * Engine::GetFrameWork()
{
	return m_framework;
}

bool Engine::GetGameStance()
{
	return m_gamePaused;
}





Graphics * Engine::GetGraphics()
{
	return m_graphics;
}



Input * Engine::GetInput()
{
	return m_input;
}

Engine * Engine::GetEngine()
{
	if (m_instance == NULL)
	{
		m_instance = new Engine();
	}
	return m_instance;
}

void Engine::Update()
{
	
		if (m_gameComponent != NULL)
		{
			m_gameComponent->Update();
		}
	float dt = Timer::GetDeltaTime();
	m_cameraControl.Update(dt);
	m_rendererManager->Update();
	(void)m_input->Update();
}

void Engine::Render()
{
	m_camera->Update();
	m_graphics->BeginScene(0.0f,0.0f,0.0f,0.0f);

	
	XMFLOAT4X4 viewMatrix       = m_camera->GetView();
	XMFLOAT4X4 projectionMatrix = m_camera->GetOrtho();

	m_rendererManager->Render(m_graphics->GetDeviceContext(), viewMatrix, projectionMatrix);
	
	if (m_gameComponent != NULL)
	{
		m_gameComponent->Render(m_graphics->GetDeviceContext(), viewMatrix, projectionMatrix);
	}




	

	m_graphics->EndScene();
}
