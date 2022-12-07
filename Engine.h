#pragma once
#include "Graphics.h"
#include "Camera.h"
#include "Input.h"
#include "GameComponent.h"
#include "ResourceManager.h"
#include "TextureShader.h"
#include "GlobalUtilities.h"
#include "RendererManager.h"
#include "PlayerManager.h"
#include "MySQLManager.h"
#include "Global.h"
#include "CameraControl.h"
#include "FrameWork.h"
#include "Canals.h"
#include "ThreadPool.h"
#include "ActionMap.h"
#include "EventManager.h"

#include <modern__.h>

class RendererManager;
class FrameWork;
struct lua_State;

#undef PlaySound
class Engine
{
	class modern_framelock m_timerLock;
	class modern_framelock m_updateLock;
	class modern_framelock m_renderLock;
	class modern_framelock m_collisionLock;
	class modern_console   m_console;
public:
	~Engine(void);

	bool InitializeGraphics(HWND hwnd);
	bool Initialize(HINSTANCE hInstance, HWND hwnd,FrameWork* framework);
	void Run();

	void Release();

	void SetGameComponent(GameComponent* gameComponent);
	void PauseGame();
	void ResumeGame();

	ISound* CreateSound(WCHAR* name);
	ISound* CreateSound(WCHAR* name,bool looping);
	ISound* CreateSound(WCHAR* name,float volume);
	ISound* CreateSound(WCHAR* name,float volume,bool looping);
	ISound* CreateSound(string name, float volume, bool looping);

	void AddMusicSound(string name, float volume, bool looping = false);
	void AddInterfaceSound(string name,const float volume);
	void AddModelPaths(string name);
	void AddFont(string filename, float width, float height);

	void PlayMusic(WCHAR* music);
	void PlayMusic(class modern_string& music);
	void StopMusic();
	void PlaySound(WCHAR* music);
	void PlaySound(class modern_string& music);
	void PlaySound(WCHAR* sound, const float volume);

	class CameraControl* const GetCameraControl();
	FrameWork* GetFrameWork();
	bool       GetGameStance();

	Graphics* GetGraphics();
	Input* GetInput();
	static Engine* GetEngine();
protected:
private:

	modern_shared<modern_timer> m_timer;
	double                      m_deltaTime;

	double GetDeltaTime() const modern_except_state;

	Engine(void);

	void Update();
	void Render();
	void PRender();

	void InitializeActionMap();

	bool m_gamePaused;

	FrameWork* m_framework;
    Graphics* m_graphics;
	Global*   m_global;
	EventManager* m_eventManager{};
	PlayerManager* m_playerManager;

	static Engine* m_instance;
	Camera* m_camera;
	Input* m_input;

	ResourceManager* m_resourceManager;
	RendererManager* m_rendererManager;
	MySQLManager*    m_sqlManager;
	GameComponent*   m_gameComponent;
	Canals           m_canals;
	CameraControl    m_cameraControl;
	//ThreadPool       m_threadPool;

	lua_State*       m_lua;

public:

	void mUpdate();
};