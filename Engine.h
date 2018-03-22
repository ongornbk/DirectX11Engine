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

class RendererManager;

#undef PlaySound
class Engine
{
public:
	~Engine(void);

	bool InitializeGraphics(HWND hwnd);
	bool Initialize(HINSTANCE hInstance, HWND hwnd);
	void Run();

	void Release();

	void SetGameComponent(GameComponent* gameComponent);
	Sound* CreateSound(WCHAR* name);
	Sound* CreateSound(WCHAR* name,bool looping);
	Sound* CreateSound(WCHAR* name,float volume);
	Sound* CreateSound(WCHAR* name,float volume,bool looping); 


	Graphics* GetGraphics();
	Input* GetInput();
	static Engine* GetEngine();
protected:
private:
	Engine(void);

	void Update();
	void Render();

    Graphics* m_graphics;
	Global*   m_global;
	static Engine* m_instance;
	Camera* m_camera;
	Input* m_input;
	//temp
	ResourceManager* m_resourceManager;
	RendererManager* m_rendererManager;
	GameComponent* m_gameComponent;
};