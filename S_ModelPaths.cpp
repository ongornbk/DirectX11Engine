#include "S_ModelPaths.h"
#include <map>
#include <fstream>
#include <sstream>
#include <streambuf>

#include <string>
#include <vector>

#pragma region
using std::string;
using std::vector;
using std::wstring;
#pragma endregion

ModelPaths::ModelPaths()
{
}

ModelPaths::ModelPaths(WCHAR * file)
{
#pragma warning(disable : 4996)
#pragma region
	using std::ifstream;
	using std::getline;
	using std::istreambuf_iterator;
	using std::istringstream;
#pragma endregion
	ifstream stream(file);
	if (!stream.good())
	{

	}
	string BUFFER((istreambuf_iterator<char>(stream)), istreambuf_iterator<char>());
	istringstream ss(BUFFER);
	vector<WCHAR*> animations;
	string token;
	while (getline(ss, token, '\n'))
	{
		wchar_t* wide_string = new wchar_t[token.length() + 1];
		wstring ws = std::wstring(token.begin(), token.end()).c_str();
		wcscpy(wide_string, ws.c_str());
		if (wcscmp(wide_string, L"NULL"))
		{
			animations.push_back(wide_string);
		}
		else
		{
			animations.push_back(NULL);
		}
	}

	ATTACK_1    = animations.at(0);
	ATTACK_2    = animations.at(1);
	GETHIT      = animations.at(2);
	KICK        = animations.at(3);
	NEUTRAL     = animations.at(4);
	RUN         = animations.at(5);
	SPECIALCAST = animations.at(6);
	SPECIAL_1   = animations.at(7);
	SPECIAL_3   = animations.at(8);
	SPECIAL_4   = animations.at(9);
	TOWNNEUTRAL = animations.at(10);
	TOWNWALK    = animations.at(11);
	WALK        = animations.at(12);
}




using std::map;

namespace
{
	static map<string, ModelPaths> m_modelPaths;
}


namespace S_ModelPaths
{
	 ModelPaths* GetModelPaths(string paths)
	{
		return &m_modelPaths[paths];
	}

	void AddModelPaths(string name,WCHAR* file)
	{
		m_modelPaths[name] = ModelPaths(file);
	}
}