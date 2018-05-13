#include "FrameWork.h"
#include "GameScene.h"
#include "SettingsC.h"
#include <iostream>
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
		//if (FAILED(GetItemByUrl(RESOURCES_URL, RESOURCES_LOCATION)))
		//{
			//SetConsoleTextAttribute(hConsole, 12);
		////	cout << "ResourceManager : Unable To Load : RESOURCES FILE" << endl;
		//	return;
		//}
		//else
		//{
		//	stream = ifstream(RESOURCES_LOCATION);
		//}
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

	/*
	int input;
	float inputf;
	cout << "Podaj poczatkowe parrametry" << endl;
	cout << "Podaj szerokosc ekranu" << endl;
	cin >> input;
	SETTINGS RESOLUTION_X = new int(input);
	cout << "Podaj wysokosc ekranu" << endl;

	cin >> input;
	SETTINGS RESOLUTION_Y = new int(input);
	cout << "Podaj ilosc jednostek" << endl;
	cin >> input;

	SETTINGS NUMBER_OF_UNITS = new int(input);
	cout << "Podaj KOLIZJE JEDNOSTEK" << endl;
	cin >> inputf;
	SETTINGS COLLISSION_RADIUS = new float(inputf);
	*/
	FrameWork* frameWork = new FrameWork();

	if (frameWork->Initialize(new GameScene))
	{
		frameWork->Run();
	}

	delete frameWork;

	return;
}