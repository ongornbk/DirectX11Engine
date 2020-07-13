
#include "Engine.h"
#include "IPP.h"
#include "SettingsC.h"
#include "LUAManager.h"
#include "LuaCallback.cpp"
#include "S_ModelPaths.h"
#include "Font.h"
#include "ShadowShader.h"
#include "CPU.h"
#include "String.h"
#include "ActionRemoveObject.h"
#include "ActionApplyColorFilter.h"
#include "ActionMessageFront.h"
#include "GarbageCollector.h"
#include <map>
#include <streambuf>
#include <fstream>
#include <istream>
#include <sstream>
#include <stack>
#include <thread>

Engine* Engine::m_instance = nullptr;



namespace
{

	static Sound*                  m_playingMusic = nullptr;

}






Engine::~Engine(void)
{

	ThreadPoolHandle tph;
	tph.wait();

	if (m_graphics)
	{
		delete m_graphics;
		m_graphics = nullptr;
	}
	if (m_rendererManager)
	{
		delete m_rendererManager;
		m_rendererManager = nullptr;
	}
	if (m_camera)
	{
		delete m_camera;
		m_camera = nullptr;
	}
	if (m_resourceManager)
	{
		delete m_resourceManager;
		m_resourceManager = nullptr;
	}
	if (m_input)
	{
		delete m_input;
		m_input = nullptr;
	}
	if (m_global)
	{
		delete m_global;
		m_global = nullptr;
	}
	if (m_gameComponent)
	{
	//	delete m_gameComponent;
		m_gameComponent = nullptr;
	}
	Font::ReleaseFonts();
	lua::Close();
}

Engine::Engine(void)
{
#pragma region
	m_gamePaused      = FALSE;
	m_graphics        = nullptr;
	m_rendererManager = nullptr;
	m_camera          = nullptr;
	m_resourceManager = nullptr;
	m_input           = nullptr;
	m_gameComponent   = nullptr;
	m_global          = nullptr;
	m_framework       = nullptr;
	m_lua             = nullptr;
#pragma endregion
}

bool Engine::InitializeGraphics(HWND hwnd)
{
	m_graphics = new Graphics();
	return m_graphics->InitializeDirectX(hwnd);
}



bool Engine::Initialize(HINSTANCE hInstance, HWND hwnd,FrameWork* framework)
{

	ipp::Console::Println("Engine::Initialize");

	Initialize_CPU();

	ipp::Console::Println("Engine::InitializeCpu");

#define LOADSHADER  m_resourceManager->LoadShaderResource(hwnd, 
#define END );



	m_global = Global::GetInstance();
	Tree::SetGlobal(m_global);
	m_camera = new Camera();
	m_resourceManager = ResourceManager::GetInstance();

	ipp::Console::Println("Engine::InitializeRM");

	InitializeActionMap();

	lua_callback::Initialize(this);

	ipp::Console::Println("Engine::InitializeLCB");

	lua_callback::SetResourceManager(m_resourceManager);
	lua_callback::SetCamera(m_camera);

	rm::SetDevice(m_graphics->GetDevice());

	lua::Open();
	lua_callback::RegisterFunctions();
	lua::Execute(lua::LUA_LOCATION_ENGINE_INITIALIZATION);

	ipp::Console::Println("Engine::Lua Open and exec");

#pragma region
	LOADSHADER  L"x64/Release/bin/Shaders/texture.fx"                              END
	LOADSHADER  L"x64/Release/bin/Shaders/tile.fx"                                 END
	LOADSHADER  L"x64/Release/bin/Shaders/units.fx"                                END
	LOADSHADER  L"x64/Release/bin/Shaders/shadow.fx"                               END
	LOADSHADER  L"x64/Release/bin/Shaders/select.fx"                               END
	TextureShader* uiShader  = GETSHADER "texture.fx"                END
	TextureShader* unitsShader = GETSHADER "units.fx"                END
	TextureShader* shadowsShader = GETSHADER "shadow.fx" END
	TextureShader* selectShader = GETSHADER "select.fx" END
#pragma endregion
	
	m_input = new Input();
	m_input->Initialize(hInstance, hwnd,Settings::GetResolutionX(), Settings::GetResolutionY());
	lua_callback::SetInput(m_input);

	m_rendererManager = new RendererManager(this, unitsShader,uiShader,shadowsShader,selectShader);
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
		ipp::Console::Println("No game component!", ipp::TextColors::RED);
	}
	
	


	return true;
}

namespace
{
	clock_t deltaTime = 0;
	uint32_t frames = 0;
	double  frameRate = 30;
	double  averageFrameTimeMilliseconds = 33.333;

	extern "C"
	{
		double clockToMilliseconds(clock_t ticks) noexcept {
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

	lua::Execute(lua::LUA_LOCATION_RENDERAFTER);

	clock_t endFrame = clock();

	deltaTime += endFrame - beginFrame;
	frames++;

	if (clockToMilliseconds(deltaTime)>1000.0) {
		frameRate = (double)frames*0.5 + frameRate * 0.5;
		frames = 0;
		deltaTime -= CLOCKS_PER_SEC;
		averageFrameTimeMilliseconds = 1000.0 / (frameRate == 0 ? 0.001 : frameRate);

		const  int32 fps = ( int32)(1000 / averageFrameTimeMilliseconds);

		m_rendererManager->SetFps(fps);

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
	sound->SetVolume(volume);
	sound->SetLooping(looping);
	return sound;
}

Sound * Engine::CreateSound(string name, float volume, bool looping)
{
	class Sound* const sound = m_resourceManager->GetSoundByName((char*)name.c_str());
	if (sound)
	{
		sound->SetVolume(volume);
		sound->SetLooping(looping);
	}
	else
	{
		ipp::Console::SetTextColor(ipp::RED);
		ipp::Console::Println("Cannot get sound : " + name);
	}
	return sound;
}

void Engine::AddMusicSound(string name, float volume,bool looping)
{
	m_canals.__AddSound(CanalType::CTMUSIC, name, CreateSound(name, volume, looping));
}

void Engine::AddInterfaceSound(string name,const float volume)
{
	m_canals.__AddSound(CanalType::CTINTERFACE, name, CreateSound(name, volume, false));
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
	delete[] wide_string;
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

void Engine::PlaySound(WCHAR * music)
{
	wstring tmp0 = wstring(music);
	string  tmp1 = string(tmp0.begin(), tmp0.end());
	class Sound* sound = m_canals.__GetSound(tmp1);
	sound->Play();
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
	{
		class Canals* const canals = Canals::GetInstance();
		if (canals)
			canals->Update();
	}
		if (m_gameComponent != nullptr)
		{
			m_gameComponent->Update();
		}
	float dt = ipp::Timer::GetDeltaTime();
	m_cameraControl.Update(dt);
	Timer::Update(dt);
	m_rendererManager->Update();
	(void)m_input->Update();


	
}

void Engine::Render()
{

	{
		{
			class GarbageCollector* gbc = GarbageCollector::GetInstance();
			gbc->Update();
		}
		
		{

			m_graphics->BeginScene(0.0f, 0.0f, 0.0f, 0.0f);
			m_camera->Update();

			XMFLOAT4X4 viewMatrix = m_camera->GetView();
			XMFLOAT4X4 projectionMatrix = m_camera->GetOrtho();

			m_rendererManager->Render(m_graphics->GetDeviceContext(), viewMatrix, projectionMatrix);

			if (m_gameComponent != NULL)
			{
				m_gameComponent->Render(m_graphics->GetDeviceContext(), viewMatrix, projectionMatrix);
			}






			m_graphics->EndScene();

		}
	}

}

extern "C"
{

	_Use_decl_annotations_
	class _Out_ IAction* _stdcall __action__remove__object__(class ActionMap* _In_ map)
	{
		class EObject* const object = (class EObject* const)(map->PopPointer());
		class IAction* const action = new ActionRemoveObject((object));
		return action;
	}

	_Use_decl_annotations_
		class _Out_ IAction* _stdcall __action__apply__color__filter__(class ActionMap* _In_ map)
	{
		class Unit* const object = (class Unit* const)map->PopPointer();
		struct DirectX::XMFLOAT4 color;
		color.x = (float)(int)(int64_t)map->PopBasic().type__int64;
		color.y = (float)(int)(int64_t)map->PopBasic().type__int64;
		color.z = (float)(int)(int64_t)map->PopBasic().type__int64;
		color.w = (float)(int)(int64_t)map->PopBasic().type__int64;
		class IAction* const action = new ActionApplyColorFilter(object,color);
		return action;
	}

	_Use_decl_annotations_
		class _Out_ IAction* _stdcall __action__message__front(class ActionMap* const _In_ map)
	{
		class EObject* const object = (class EObject* const)map->PopPointer();
		class IAction* const action = new ActionMessageFront(object);
		return action;
	}

}

void Engine::InitializeActionMap()
{
	class ActionMap* const map = ActionMap::GetInstance();
	map->AddAction(__action__remove__object__, "RemoveObject");
	map->AddAction(__action__apply__color__filter__, "ApplyColorFilter");
	map->AddAction(__action__message__front, "MessageFront");
}
