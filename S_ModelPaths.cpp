#include "S_ModelPaths.h"
#include <map>
#include <fstream>
#include <sstream>
#include <streambuf>

#include <string>
#include <vector>

#include "IPP.h"

#include <modern__.h>

#pragma region
using std::string;
using std::vector;
using std::wstring;
#pragma endregion

ModelPaths::ModelPaths()
{
	ZeroMemory(m_modelPath, sizeof(WCHAR*) * 15);
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
		ipp::Console::SetTextColor(MODERN_CONSOLE_TEXT_COLOR::RED);
		ipp::Console::Println("Bad stream : ");
	}
	std::string BUFFER((istreambuf_iterator<char>(stream)), istreambuf_iterator<char>());
	istringstream ss(BUFFER);
	modern_array<WCHAR*> animations;
	std::string token;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	while (getline(ss, token, '\n'))
	{
		wchar_t* wide_string = new wchar_t[token.length() + 1]; //do not delete
		wstring ws = (WCHAR*)converter.from_bytes(token).c_str();
		wcscpy(wide_string, std::wstring(token.begin(), token.end()).c_str());
		if (wcscmp(wide_string, L"NULL"))
		{
			animations.push_back(wide_string);
		}
		else
		{
			animations.push_back(NULL);
		}
	}
	//ipp::Console::SetTextColor(ipp::DARKGRAY);
	//ipp::Console::Print("Loading started for : ");
	//ipp::Console::Println(animations.size());
	//for (size_t i = 0; i = min(animations.size(),13); i++)
	//{
	//	m_modelPath[i] = animations.at(i);
	//	ipp::Console::SetTextColor(ipp::DARKGRAY);
	//	ipp::Console::Print("Loading : ");
	//	ipp::Console::Println(animations.at(i));
	//}

	m_rotations = modern_string(animations.at(0)).to_int32();
	m_leaveCorpse = modern_string(animations.at(1)).to_bool();
	m_frames[0] = modern_string(animations.at(2)).to_int32();
	m_frames[1] = modern_string(animations.at(3)).to_int32();
	m_frames[2] = modern_string(animations.at(4)).to_int32();
	m_frames[3] = modern_string(animations.at(5)).to_int32();
	m_frames[4] = modern_string(animations.at(6)).to_int32();
	m_frames[5] = modern_string(animations.at(7)).to_int32();
	m_frames[6] = modern_string(animations.at(8)).to_int32();
	m_frames[7] = modern_string(animations.at(9)).to_int32();
	m_frames[8] = modern_string(animations.at(10)).to_int32();
	m_frames[9] = modern_string(animations.at(11)).to_int32();
	m_frames[10] = modern_string(animations.at(12)).to_int32();
	m_frames[11] = modern_string(animations.at(13)).to_int32();
	m_frames[12] = modern_string(animations.at(14)).to_int32();
	m_frames[13] = modern_string(animations.at(15)).to_int32();
	m_frames[14] = modern_string(animations.at(16)).to_int32();

	m_sizes[0] = modern_string(animations.at(17)).to_float();
	m_sizes[1] = modern_string(animations.at(18)).to_float();
	m_sizes[2] = modern_string(animations.at(19)).to_float();
	m_sizes[3] = modern_string(animations.at(20)).to_float();
	m_sizes[4] = modern_string(animations.at(21)).to_float();
	m_sizes[5] = modern_string(animations.at(22)).to_float();
	m_sizes[6] = modern_string(animations.at(23)).to_float();
	m_sizes[7] = modern_string(animations.at(24)).to_float();
	m_sizes[8] = modern_string(animations.at(25)).to_float();
	m_sizes[9] = modern_string(animations.at(26)).to_float();
	m_sizes[10] = modern_string(animations.at(27)).to_float();
	m_sizes[11] = modern_string(animations.at(28)).to_float();
	m_sizes[12] = modern_string(animations.at(29)).to_float();
	m_sizes[13] = modern_string(animations.at(30)).to_float();
	m_sizes[14] = modern_string(animations.at(31)).to_float();

	ATTACK_1    = animations.at(32);
	ATTACK_2    = animations.at(33);
	GETHIT      = animations.at(34);
	KICK        = animations.at(35);
	NEUTRAL     = animations.at(36);
	RUN         = animations.at(37);
	SPECIALCAST = animations.at(38);
	SPECIAL_1   = animations.at(39);
	SPECIAL_2   = animations.at(40);
	SPECIAL_3   = animations.at(41);
	TOWNNEUTRAL = animations.at(42);
	TOWNWALK    = animations.at(43);
	WALK        = animations.at(44);
	DEATH       = animations.at(45);
	DEAD        = animations.at(46);

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