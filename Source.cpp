#include "FrameWork.h"
#include "GameScene.h"
#include "SettingsC.h"
#include "IPP.h"
#include "XMLParser.h"
#include "LUAManager.h"
#include <thread>
#include <fstream>
#include <sstream>
#include <streambuf>

#pragma region
#define SETTINGS Settings::get()->
#define SETTINGS_LOCATION "../settings/settings.file"
#define SETTINGS_NUMBER_OF_ARGUMENTS 4U
#pragma endregion

using std::string;



void main(int argc,char** argv)
{
#pragma region
	using std::ifstream;
	using std::getline;
	using std::atoi;
	using std::atof;
#pragma endregion



	ifstream stream(SETTINGS_LOCATION);
	if (!stream.good())
	{
		ipp::Console::SetTextColor(ipp::RED);
		ipp::Console::Println("Bad stream : " + string(SETTINGS_LOCATION));
	}
	std::string BUFFER((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
	
	//XMLParser xml;
	//xml.Parse(BUFFER);
	
	istringstream ss(BUFFER);
	vector<string> settings;
	string token, token2;
	while (getline(ss, token, '\n'))
	{
		settings.push_back(token);
	}

	if (settings.size() == SETTINGS_NUMBER_OF_ARGUMENTS)
	{
		ipp::Console::SetTextColor(ipp::DARKGRAY);
		ipp::Console::Print("Settings::Resolution : ");
		ipp::Console::Print(settings.at(0));
		ipp::Console::Print(".");
		ipp::Console::Println(settings.at(1));
		ipp::Console::Print("Settings::Fullscreen : ");
		ipp::Console::Println(settings.at(2));
		ipp::Console::Print("Settings::VSync : ");
		ipp::Console::Println(settings.at(3));
		Settings::Initialize(atoi(settings.at(0).c_str()), atoi(settings.at(1).c_str()), GetSystemMetrics(SM_CXSCREEN),
			GetSystemMetrics(SM_CYSCREEN), (int32_t)std::thread::hardware_concurrency(), (bool)atoi(settings.at(2).c_str()), (bool)atoi(settings.at(3).c_str()));
	}
	else
	{
		ipp::Console::SetTextColor(ipp::RED);
		ipp::Console::Print("Invalid number of arguments in settings.file! : ");
		ipp::Console::Println(settings.size());
		Settings::Initialize(800,600, GetSystemMetrics(SM_CXSCREEN),
			GetSystemMetrics(SM_CYSCREEN), (int32_t)std::thread::hardware_concurrency(), 0, 0);
	}
	

	FrameWork* frameWork = new FrameWork();

	if (frameWork->Initialize(new GameScene))
	{
		frameWork->Run();
	}

	delete frameWork;

	return;
}