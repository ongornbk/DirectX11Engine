#pragma once
#define DEBUGG_DEV_MODE
#define DIRECTSOUND_VERSION  0x0800

	static const int SCREEN_WIDTH = 1920;
	static const int SCREEN_HEIGHT = 1080;
	static const int WINDOW_POS_X = 1630;
	static const int WINDOW_POS_Y = 85;



const float SCREEN_DEPTH = 1000.0f;
const float	SCREEN_NEAR = 0.1f;
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;

#define TILE_MAP_SIZE 1024

#pragma region
#define SETTINGS Settings::get()->
#define CAMERA   Camera::GetCurrentCamera()->
#define GLOBAL   Global::GetInstance()->
#define GRAPHICS Engine::GetEngine()->GetGraphics()->
#define ENGINE Engine::GetEngine()->
#pragma endregion