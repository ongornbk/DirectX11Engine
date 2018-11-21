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
	
	Settings::Initialize(atoi(settings.at(0).c_str()), atoi(settings.at(1).c_str()), GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN), (int32_t)std::thread::hardware_concurrency(),(bool)atoi(settings.at(2).c_str()), (bool)atoi(settings.at(3).c_str()));

	FrameWork* frameWork = new FrameWork();

	if (frameWork->Initialize(new GameScene))
	{
		frameWork->Run();
	}

	delete frameWork;

	return;
}