#include "FrameWork.h"
#include "GameScene.h"
#include "MainMenu.h"
#include "SettingsC.h"
#include "IPP.h"
#include "LUAManager.h"
#include "MPManager.h"
#include "GPUMemory.h"
#include <thread>
#include <fstream>
#include <sstream>
#include <streambuf>
#include "modern/modern_vector.h"
#include "modern/modern_file.h"
#include "modern/modern_string.h"
#include "modern/modern_mqueue.h"
#include "modern/modern_thread_pool.h"
#include "modern/modern_static_array.h"
#include "modern/modern_spinlock.h"
#include "Unit.h"

#pragma region
#define SETTINGS Settings::get()->
#define SETTINGS_LOCATION "../settings/settings.file"
#define SETTINGS_LOCATION_WIDE L"../settings/settings.file"
#define SETTINGS_LOCATION2 "X64/Release/bin/settings/settings.file"
#define SETTINGS_NUMBER_OF_ARGUMENTS 5U
#pragma endregion

using std::string;

void main(const int argc,char** const argv)
{
//	modern_string A0 = L"12345";
//	modern_string A1 = L"-12345";
//
//	modern_cstring A2 = "12345";
//	modern_cstring A3 = "-12345";
//
//	std::cout << A0.to_int32() << " : " << A1.to_int32() << std::endl;
//	std::cout << A2.to_int32() << " : " << A3.to_int32() << std::endl << std::endl;
//
//	std::cout << A0.c_str() << " : " << A1.c_str() << std::endl;
//	std::cout << A2.c_str() << " : " << A3.c_str() << std::endl;
// 
//
//
//
//
//	getchar();
//	return;

	MPManager::Initialize(1ull);
	GPUMemory::Initialize();


	{

		std::ifstream stream(SETTINGS_LOCATION);
		
		if (!stream.good())
		{
			ipp::Console::SetTextColor(MODERN_CONSOLE_TEXT_COLOR::RED);
			ipp::Console::Println("Bad stream : " + string(SETTINGS_LOCATION));
			stream.close();
			stream.open(SETTINGS_LOCATION2);
			if (!stream.good())
			{
				ipp::Console::SetTextColor(MODERN_CONSOLE_TEXT_COLOR::RED);
				ipp::Console::Println("Bad stream : " + string(SETTINGS_LOCATION2));
				return;
			}
		}

		std::string BUFFER((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

		//XMLParser xml;
		//xml.Parse(BUFFER);

		istringstream ss(BUFFER);
		modern_vector<string> settings;
		string token, token2;
		while (getline(ss, token, '\n'))
		{
			settings.push_backr(token);
		}

		if (settings.size() == SETTINGS_NUMBER_OF_ARGUMENTS)
		{
			ipp::Console::SetTextColor(MODERN_CONSOLE_TEXT_COLOR::DARKGRAY);
			ipp::Console::Print("Settings::Resolution : ");
			ipp::Console::Print(settings.at(0));
			ipp::Console::Print(".");
			ipp::Console::Println(settings.at(1));
			ipp::Console::Print("Settings::Fullscreen : ");
			ipp::Console::Println(settings.at(2));
			ipp::Console::Print("Settings::VSync : ");
			ipp::Console::Println(settings.at(3));
			Settings::Initialize(
				std::atoi(settings.at(0).c_str()),//ResolutionX
				std::atoi(settings.at(1).c_str()),//ResolutionY
				GetSystemMetrics(SM_CXSCREEN),//Screen Resolution X
				GetSystemMetrics(SM_CYSCREEN),//Screen Resolution Y
				(int32_t)std::thread::hardware_concurrency(),//CPU number of threads
				(bool)std::atoi(settings.at(2).c_str()),//Fullscreen
				(bool)std::atoi(settings.at(3).c_str()),//Vsync
				settings.at(4).c_str());
		}
		else
		{
			ipp::Console::SetTextColor(MODERN_CONSOLE_TEXT_COLOR::RED);
			ipp::Console::Print("Invalid number of arguments in settings.file! : ");
			ipp::Console::Println(settings.size());
			Settings::Initialize(
				800,
				600,
				GetSystemMetrics(SM_CXSCREEN),
				GetSystemMetrics(SM_CYSCREEN),
				(int32_t)std::thread::hardware_concurrency(),
				0,
				0,
				"0"
			);
		}


		class FrameWork* const frameWork = new class FrameWork();

			if (frameWork->Initialize(new class MainMenu))
			{
				frameWork->Run();
			}

		delete frameWork;
	}

	//MPManager::Get()->barrier();
	MPManager::Release();

	//sdfd.join();

	//f.join();

	//ipp::Console::GetInstance()->GetInput();

	return;
}