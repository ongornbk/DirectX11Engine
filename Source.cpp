#include "FrameWork.h"
#include "GameScene.h"
#include "SettingsC.h"
#include <iostream>
#include <thread>

#pragma region
#define SETTINGS Settings::get()->
#pragma endregion

using std::string;
using std::cin;
using std::cout;
using std::endl;

void main()
{
	SETTINGS NUMBER_OF_THREADS = new unsigned int(std::thread::hardware_concurrency());
	SETTINGS REALRESOLUTION_X = new int(GetSystemMetrics(SM_CXSCREEN));
	SETTINGS REALRESOLUTION_Y = new int(GetSystemMetrics(SM_CYSCREEN));
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
	FrameWork* frameWork = new FrameWork();

	if (frameWork->Initialize(new GameScene))
	{
		frameWork->Run();
	}

	delete frameWork;

	return;
}