#pragma once
#include "Graphics.h"
#include "Camera.h"
#include "Input.h"
#include "GameComponent.h"
#include "ResourceManager.h"
#include "TextureShader.h"
#include "GlobalUtilities.h"
#include "RendererManager.h"
#include "Global.h"
#include "CameraControl.h"
#include "FrameWork.h"
#include "Canals.h"
#include "ThreadPool.h"
#include "ActionMap.h"
#include "PTaskGCClear.h"
#include "PTaskRender.h"
#include "modern/modern_shared.h"
#include "modern/modern_timer.h"
#include "modern/modern_framelock.h"

class RendererManager;
class FrameWork;
struct lua_State;

#undef PlaySound
class Engine
{
	modern_framelock m_timerLock;
	modern_framelock m_updateLock;
	modern_framelock m_renderLock;
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

	CameraControl* GetCameraControl();
	FrameWork* GetFrameWork();
	bool       GetGameStance();

	Graphics* GetGraphics();
	Input* GetInput();
	static Engine* GetEngine();
protected:
private:

	modern_shared<modern_timer> m_timer;
	double                      m_deltaTime;

	double GetDeltaTime() const noexcept;

	Engine(void);

	friend class PTaskRender;

	void Update();
	void Render();
	void PRender();

	void InitializeActionMap();

	bool m_gamePaused;

	FrameWork* m_framework;
    Graphics* m_graphics;
	Global*   m_global;
	static Engine* m_instance;
	Camera* m_camera;
	Input* m_input;

	ResourceManager* m_resourceManager;
	RendererManager* m_rendererManager;
	GameComponent*   m_gameComponent;
	Canals           m_canals;
	CameraControl    m_cameraControl;
	ThreadPool       m_threadPool;

	lua_State*       m_lua;


};