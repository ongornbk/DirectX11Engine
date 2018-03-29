
#include "Engine.h"
#include "Timer.h"
#include "SettingsC.h"

Engine* Engine::m_instance = NULL;

static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);



namespace
{
	Sound* m_music = nullptr;
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
	if (m_console)
	{
		delete m_console;
		m_console = NULL;
	}
	if (m_gameComponent)
	{
	//	delete m_gameComponent;
		m_gameComponent = NULL;
	}
}

Engine::Engine(void)
{
	m_graphics = NULL;
	m_rendererManager = NULL;
	m_camera = NULL;
	m_resourceManager = NULL;
	m_input = NULL;
	m_gameComponent = NULL;
	m_global = NULL;
	m_console = NULL;
}

bool Engine::InitializeGraphics(HWND hwnd)
{
	m_graphics = new Graphics();
	return m_graphics->InitializeDX(hwnd);
}



bool Engine::Initialize(HINSTANCE hInstance, HWND hwnd)
{
#pragma region
#define LOADTEXTURE m_resourceManager->LoadTextureResource(m_graphics->GetDevice(),
#define LOADSHADER  m_resourceManager->LoadShaderResource(m_graphics->GetDevice(), hwnd, 
#define LOADSOUND   m_resourceManager->LoadSoundResource(
#define END );
#pragma endregion
	m_console = new Console();
	m_global = new Global();
	m_resourceManager = ResourceManager::GetInstance();

	LOADTEXTURE L"../../content/textures/barbarian_run.png"         END
	LOADTEXTURE L"../../content/textures/barbarian_townneutral.png" END
	LOADTEXTURE L"../../content/textures/enemy_walk.png"            END
	LOADTEXTURE L"../../content/textures/enemy_townneutral.png"     END
    LOADTEXTURE L"../../content/textures/barbarian_attack1.png"     END
	LOADTEXTURE L"../../content/textures/gui/ui_cursor.png"         END
	LOADTEXTURE L"../../content/textures/gui/ui_game.png"           END
	LOADTEXTURE L"../../content/textures/tiles/simplegrass.png"     END
	LOADTEXTURE L"../../content/textures/tiles/simplestone.png"     END
	LOADTEXTURE L"../../content/textures/tiles/hole.png"            END
	LOADTEXTURE L"../../content/textures/tiles/dirt.png"            END
	LOADTEXTURE L"../../content/textures/tiles/floor.png"           END
	LOADTEXTURE L"../../content/textures/tiles/stone.png"           END
	LOADTEXTURE L"../../content/textures/tiles/grasstofloor.png"    END
	LOADTEXTURE L"../../content/textures/tiles/grass.png"           END

	LOADSHADER  L"../Shaders/texture.fx"                            END

    LOADSOUND   L"../../content/Sounds/Music/harrogath.ogg"         END
	LOADSOUND   L"../../content/Sounds/FX/Attack.ogg"               END
	//m_resourceManager->LoadSoundResource(L"Sounds/FX/wha.ogg");
	TextureShader* shader = (TextureShader*)(ResourceManager::GetInstance()->GetShaderByName("texture.fx"));
	m_input = new Input();
	m_input->Initialize(hInstance, hwnd, (*(Settings::get()->RESOLUTION_X)), (*(Settings::get()->RESOLUTION_Y)));
	InitializeTemplates();
	m_rendererManager = new RendererManager(this, shader);
	


	m_camera = new Camera();
	m_camera->InitializeProjectionMatrix((float)XM_PI / 4.0f,Settings::GetAspectRatio(), SCREEN_NEAR, SCREEN_DEPTH);
	m_camera->InitializeOrthoMatrix((*(Settings::get()->RESOLUTION_X)), (*(Settings::get()->RESOLUTION_Y)), SCREEN_NEAR, SCREEN_DEPTH);
	m_camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_cameraControl.SetCurrentCamera(m_camera);
	m_graphics->Initialize();
	m_music = CreateSound(L"harrogath", 100.0f, true);

	



	

	m_music->Play();



	if(m_gameComponent!=NULL)
	{
		if (!m_gameComponent->Initialize())
		{
			return false;
		}
	}
	else
	{
		CONSOLE SetColor(CONSOLE_COLOR_RED);
		CONSOLE Println("Engine : No Game Component");
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

	//if you really want FPS
	if (clockToMilliseconds(deltaTime)>1000.0) { //every second
		frameRate = (double)frames*0.5 + frameRate * 0.5; //more stable
		frames = 0;
		deltaTime -= CLOCKS_PER_SEC;
		averageFrameTimeMilliseconds = 1000.0 / (frameRate == 0 ? 0.001 : frameRate);

//		if (vsync)
		int fps = (int)(1000 / averageFrameTimeMilliseconds);
			if (fps < 30)
			{
				SetConsoleTextAttribute(hConsole, 12);
		}
			else if (fps < 45)
			{
				SetConsoleTextAttribute(hConsole, 11);
			}
			else
				SetConsoleTextAttribute(hConsole, 10);
			std::cout << "FPS : " << fps << std::endl;
//		else
//			std::cout << "CPU time was:" << averageFrameTimeMilliseconds << std::endl;
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

CameraControl * Engine::GetCameraControl()
{
	return &m_cameraControl;
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
