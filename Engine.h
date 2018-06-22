#pragma once
#include "Graphics.h"
#include "Camera.h"
#include "Input.h"
#include "GameComponent.h"
#include "ResourceManager.h"
#include "EntityManager.h"
#include "TextureShader.h"
#include "GlobalUtilities.h"
#include "RendererManager.h"
#include "Global.h"
#include "CameraControl.h"
#include "FrameWork.h"
#include "Canals.h"

class RendererManager;
class FrameWork;
struct lua_State;

#undef PlaySound
class Engine
{
public:
	~Engine(void);

	bool InitializeGraphics(HWND hwnd);
	bool Initialize(HINSTANCE hInstance, HWND hwnd,FrameWork* framework);
	void Run();

	void Release();

	void SetGameComponent(GameComponent* gameComponent);
	void PauseGame();
	void ResumeGame();

	Sound* CreateSound(WCHAR* name);
	Sound* CreateSound(WCHAR* name,bool looping);
	Sound* CreateSound(WCHAR* name,float volume);
	Sound* CreateSound(WCHAR* name,float volume,bool looping);
	Sound* CreateSound(string name, float volume, bool looping);

	void AddMusicSound(string name, float volume, bool looping = false);
	void AddModelPaths(string name);

	void PlayMusic(WCHAR* music);

	CameraControl* GetCameraControl();
	FrameWork* GetFrameWork();
	bool       GetGameStance();

	Graphics* GetGraphics();
	Input* GetInput();
	static Engine* GetEngine();
protected:
private:
	Engine(void);


	void Update();
	void Render();

	volatile bool m_gamePaused;

	FrameWork* m_framework;
    Graphics* m_graphics;
	Global*   m_global;
	static Engine* m_instance;
	Camera* m_camera;
	Input* m_input;
	//temp
	ResourceManager* m_resourceManager;
	RendererManager* m_rendererManager;
	GameComponent*   m_gameComponent;
	Canals           m_canals;
	CameraControl    m_cameraControl;

	lua_State*       m_lua;
};