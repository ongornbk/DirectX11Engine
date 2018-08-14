#include "ResourceManager.h"
#include "Font.h"
#include "Onion.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <iostream>


#define FONTPATH "../../content/Textures/font/"

using Onion::Console;

namespace
{
	static std::vector<Font*> m_fonts;
}


Font::Font(float width, float height, std::string filename,bool upper)
{
	ZeroMemory(m_char, 255);
	this->m_name = filename;
	this->m_width = width;
	this->m_height = height;
	this->m_flag = upper;
	this->m_name = filename;

	int pos = (int)m_name.find_last_of("/");
	if (pos >= 0)
	{
		m_name = m_name.substr(pos + 1, m_name.length());
	}
	m_name = m_name.substr(0, m_name.find("."));
}


Font::~Font()
{

}

void Font::LoadFontFromFile(std::string filename,float width,float height)
{
	Font* font = new Font(width,height,filename);


#pragma warning(disable : 4996)
#pragma region
	using std::ifstream;
	using std::getline;
	using std::istreambuf_iterator;
	using std::istringstream;
	using std::string;
#pragma endregion

	ifstream stream(filename);
	if (!stream.good())
	{
		Console::SetTextColor(Onion::RED);
		Console::Println("Bad stream : " + filename);
	}
	string BUFFER((istreambuf_iterator<char>(stream)), istreambuf_iterator<char>());
	istringstream ss(BUFFER);
	std::vector<float> coordinates;
	string token,token2;

	

	while (getline(ss, token, '\n'))
	{
		if (!token.empty())
		{
			std::stringstream ss(token);
			while (getline((ss), token2, ' '))
			{
				coordinates.push_back((float)atoi(token2.c_str()));
			}
		}
	}

	std::reverse(coordinates.begin(), coordinates.end());

	font->InitializeCoordinates(coordinates);
	m_fonts.push_back(font);

	

}



Font * Font::GetFontByName(std::string name)
{
	for (int i = 0; i < (int)m_fonts.size(); ++i)
	{
		if (!strcmp(name.c_str(), (m_fonts[i]->m_name).c_str()))
		{
			return m_fonts[i];
		}

	}
	return NULL;
}

void Font::ReleaseFonts()
{
	for (auto && font : m_fonts)
	{
		delete font;
		font = NULL;
	}
}

std::string Font::GetName()
{
	return "ExocetLight";
}

float * Font::GetCoordsOfLetter(char letter)
{
	float f[6];
	f[0] = m_width;
	f[1] = m_height;
	f[2] = m_char[letter].m_left;
	f[3] = m_char[letter].m_top;
	f[4] = m_char[letter].m_right;
	f[5] = m_char[letter].m_bottom;
	return f;
}

void Font::InitializeCoordinates(std::vector<float> coords)
{
	std::reverse(coords.begin(), coords.end());
	m_char['a'].m_left = coords.at(0);
	m_char['a'].m_top = coords.at(1);
	m_char['a'].m_right = coords.at(2);
	m_char['a'].m_bottom = coords.at(3);
	if (m_flag)
	{
		m_char['A'] = m_char['a'];
	}
}


