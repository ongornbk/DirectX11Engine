#include "FrameWork.h"
#include "GameScene.h"
#include "SettingsC.h"
#include "Onion.h"
#include <thread>
#include <fstream>
#include <sstream>
#include <streambuf>

#pragma region
#define SETTINGS Settings::get()->
#define SETTINGS_LOCATION "../settings/settings.file"
#pragma endregion

using std::string;
using std::cin;
using std::cout;
using std::endl;

void main(int argc,char** argv)
{
#pragma region
	using std::ifstream;
	using std::getline;
	using std::atoi;
	using std::atof;
#pragma endregion

	SETTINGS NUMBER_OF_THREADS = new unsigned int(std::thread::hardware_concurrency());
	SETTINGS REALRESOLUTION_X = new int(GetSystemMetrics(SM_CXSCREEN));
	SETTINGS REALRESOLUTION_Y = new int(GetSystemMetrics(SM_CYSCREEN));

	ifstream stream(SETTINGS_LOCATION);
	if (!stream.good())
	{
		Onion::Console::SetTextColor(Onion::RED);
		Onion::Console::Println("Bad stream : " + string(SETTINGS_LOCATION));
	}
	std::string BUFFER((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
	istringstream ss(BUFFER);
	vector<string> settings;
	string token, token2;
	while (getline(ss, token, '\n'))
	{
		settings.push_back(token);
	}
	
	SETTINGS RESOLUTION_X = new int(atoi(settings.at(0).c_str()));
	SETTINGS RESOLUTION_Y = new int(atoi(settings.at(1).c_str()));
	SETTINGS NUMBER_OF_UNITS = new int(atoi(settings.at(2).c_str()));
	SETTINGS COLLISSION_RADIUS = new float((float)atof(settings.at(3).c_str()));


	FrameWork* frameWork = new FrameWork();

	if (frameWork->Initialize(new GameScene))
	{
		frameWork->Run();
	}

	delete frameWork;

	return;
}