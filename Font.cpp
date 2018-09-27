#include "ResourceManager.h"
#include "Font.h"
#include "IPP.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <iostream>


#define FONTPATH "../../content/Textures/font/"

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
		ipp::Console::SetTextColor(ipp::RED);
		ipp::Console::Println("Bad stream : " + filename);
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

FLOATX6 Font::GetCoordsOfLetter(char letter)
{
	FLOATX6 f;
	f.__f32[0] = m_width;
	f.__f32[1] = m_height;
	f.__f32[2] = m_char[letter].m_left;
	f.__f32[3] = m_char[letter].m_top;
	f.__f32[4] = m_char[letter].m_right;
	f.__f32[5] = m_char[letter].m_bottom;
	return f;
}

float Font::GetLeftOfLetter(char letter)
{
	return m_char[letter].m_left;
}

float Font::GetWidthOfLetter(char letter)
{
	return (m_char[letter].m_right) - (m_char[letter].m_left);
}

void Font::InitializeCoordinates(std::vector<float> coords)
{
	std::reverse(coords.begin(), coords.end());


	m_char['a'].m_left = coords.at(0);
	m_char['a'].m_top = coords.at(1);
	m_char['a'].m_right = coords.at(2);
	m_char['a'].m_bottom = coords.at(3);
	m_char['b'].m_left = coords.at(4);
	m_char['b'].m_top = coords.at(5);
	m_char['b'].m_right = coords.at(6);
	m_char['b'].m_bottom = coords.at(7);
	m_char['c'].m_left = coords.at(8);
	m_char['c'].m_top = coords.at(9);
	m_char['c'].m_right = coords.at(10);
	m_char['c'].m_bottom = coords.at(11);
	m_char['d'].m_left = coords.at(12);
	m_char['d'].m_top = coords.at(13);
	m_char['d'].m_right = coords.at(14);
	m_char['d'].m_bottom = coords.at(15);
	m_char['e'].m_left = coords.at(16);
	m_char['e'].m_top = coords.at(17);
	m_char['e'].m_right = coords.at(18);
	m_char['e'].m_bottom = coords.at(19);
	m_char['f'].m_left = coords.at(20);
	m_char['f'].m_top = coords.at(21);
	m_char['f'].m_right = coords.at(22);
	m_char['f'].m_bottom = coords.at(23);
	m_char['g'].m_left = coords.at(24);
	m_char['g'].m_top = coords.at(25);
	m_char['g'].m_right = coords.at(26);
	m_char['g'].m_bottom = coords.at(27);
	m_char['h'].m_left = coords.at(28);
	m_char['h'].m_top = coords.at(29);
	m_char['h'].m_right = coords.at(30);
	m_char['h'].m_bottom = coords.at(31);
	m_char['i'].m_left = coords.at(32);
	m_char['i'].m_top = coords.at(33);
	m_char['i'].m_right = coords.at(34);
	m_char['i'].m_bottom = coords.at(35);
	m_char['j'].m_left = coords.at(36);
	m_char['j'].m_top = coords.at(37);
	m_char['j'].m_right = coords.at(38);
	m_char['j'].m_bottom = coords.at(39);
	m_char['k'].m_left = coords.at(40);
	m_char['k'].m_top = coords.at(41);
	m_char['k'].m_right = coords.at(42);
	m_char['k'].m_bottom = coords.at(43);
	m_char['l'].m_left = coords.at(44);
	m_char['l'].m_top = coords.at(45);
	m_char['l'].m_right = coords.at(46);
	m_char['l'].m_bottom = coords.at(47);
	m_char['m'].m_left = coords.at(48);
	m_char['m'].m_top = coords.at(49);
	m_char['m'].m_right = coords.at(50);
	m_char['m'].m_bottom = coords.at(51);
	m_char['n'].m_left = coords.at(52);
	m_char['n'].m_top = coords.at(53);
	m_char['n'].m_right = coords.at(54);
	m_char['n'].m_bottom = coords.at(55);
	m_char[' '].m_left = coords.at(56);
	m_char[' '].m_top = coords.at(57);
	m_char[' '].m_right = coords.at(58);
	m_char[' '].m_bottom = coords.at(59);
	m_char['o'].m_left = coords.at(60);
	m_char['o'].m_top = coords.at(61);
	m_char['o'].m_right = coords.at(62);
	m_char['o'].m_bottom = coords.at(63);
	m_char['p'].m_left = coords.at(64);
	m_char['p'].m_top = coords.at(65);
	m_char['p'].m_right = coords.at(66);
	m_char['p'].m_bottom = coords.at(67);
	m_char['q'].m_left = coords.at(68);
	m_char['q'].m_top = coords.at(69);
	m_char['q'].m_right = coords.at(70);
	m_char['q'].m_bottom = coords.at(71);
	m_char['r'].m_left = coords.at(72);
	m_char['r'].m_top = coords.at(73);
	m_char['r'].m_right = coords.at(74);
	m_char['r'].m_bottom = coords.at(75);
	m_char['s'].m_left = coords.at(76);
	m_char['s'].m_top = coords.at(77);
	m_char['s'].m_right = coords.at(78);
	m_char['s'].m_bottom = coords.at(79);
	m_char['t'].m_left = coords.at(80);
	m_char['t'].m_top = coords.at(81);
	m_char['t'].m_right = coords.at(82);
	m_char['t'].m_bottom = coords.at(83);
	m_char['u'].m_left = coords.at(84);
	m_char['u'].m_top = coords.at(85);
	m_char['u'].m_right = coords.at(86);
	m_char['u'].m_bottom = coords.at(87);
	m_char['v'].m_left = coords.at(88);
	m_char['v'].m_top = coords.at(89);
	m_char['v'].m_right = coords.at(90);
	m_char['v'].m_bottom = coords.at(91);
	m_char['w'].m_left = coords.at(92);
	m_char['w'].m_top = coords.at(93);
	m_char['w'].m_right = coords.at(94);
	m_char['w'].m_bottom = coords.at(95);
	m_char['x'].m_left = coords.at(96);
	m_char['x'].m_top = coords.at(97);
	m_char['x'].m_right = coords.at(98);
	m_char['x'].m_bottom = coords.at(99);
	m_char['y'].m_left = coords.at(100);
	m_char['y'].m_top = coords.at(101);
	m_char['y'].m_right = coords.at(102);
	m_char['y'].m_bottom = coords.at(103);
	m_char['z'].m_left = coords.at(104);
	m_char['z'].m_top = coords.at(105);
	m_char['z'].m_right = coords.at(106);
	m_char['z'].m_bottom = coords.at(107);
	m_char['1'].m_left = coords.at(108);
	m_char['1'].m_top = coords.at(109);
	m_char['1'].m_right = coords.at(110);
	m_char['1'].m_bottom = coords.at(111);
	m_char['2'].m_left = coords.at(112);
	m_char['2'].m_top = coords.at(113);
	m_char['2'].m_right = coords.at(114);
	m_char['2'].m_bottom = coords.at(115);
	m_char['3'].m_left = coords.at(116);
	m_char['3'].m_top = coords.at(117);
	m_char['3'].m_right = coords.at(118);
	m_char['3'].m_bottom = coords.at(119);
	m_char['4'].m_left = coords.at(120);
	m_char['4'].m_top = coords.at(121);
	m_char['4'].m_right = coords.at(122);
	m_char['4'].m_bottom = coords.at(123);
	m_char['5'].m_left = coords.at(124);
	m_char['5'].m_top = coords.at(125);
	m_char['5'].m_right = coords.at(126);
	m_char['5'].m_bottom = coords.at(127);
	m_char['6'].m_left = coords.at(128);
	m_char['6'].m_top = coords.at(129);
	m_char['6'].m_right = coords.at(130);
	m_char['6'].m_bottom = coords.at(131);
	m_char['7'].m_left = coords.at(132);
	m_char['7'].m_top = coords.at(133);
	m_char['7'].m_right = coords.at(134);
	m_char['7'].m_bottom = coords.at(135);
	m_char['8'].m_left = coords.at(136);
	m_char['8'].m_top = coords.at(137);
	m_char['8'].m_right = coords.at(138);
	m_char['8'].m_bottom = coords.at(139);
	m_char['9'].m_left = coords.at(140);
	m_char['9'].m_top = coords.at(141);
	m_char['9'].m_right = coords.at(142);
	m_char['9'].m_bottom = coords.at(143);
	m_char['0'].m_left = coords.at(144);
	m_char['0'].m_top = coords.at(145);
	m_char['0'].m_right = coords.at(146);
	m_char['0'].m_bottom = coords.at(147);
	m_char['('].m_left = coords.at(148);
	m_char['('].m_top = coords.at(149);
	m_char['('].m_right = coords.at(150);
	m_char['('].m_bottom = coords.at(151);
	m_char['$'].m_left = coords.at(152);
	m_char['$'].m_top = coords.at(153);
	m_char['$'].m_right = coords.at(154);
	m_char['$'].m_bottom = coords.at(155);
	m_char['€'].m_left = coords.at(156);
	m_char['€'].m_top = coords.at(157);
	m_char['€'].m_right = coords.at(158);
	m_char['€'].m_bottom = coords.at(159);
	m_char['.'].m_left = coords.at(160);
	m_char['.'].m_top = coords.at(161);
	m_char['.'].m_right = coords.at(162);
	m_char['.'].m_bottom = coords.at(163);

	if (m_flag)
	{
		m_char['A'] = m_char['a'];
		m_char['B'] = m_char['b'];
		m_char['C'] = m_char['c'];
		m_char['D'] = m_char['d'];
		m_char['E'] = m_char['e'];
		m_char['F'] = m_char['f'];
		m_char['G'] = m_char['g'];
		m_char['H'] = m_char['h'];
		m_char['I'] = m_char['i'];
		m_char['J'] = m_char['j'];
		m_char['K'] = m_char['k'];
		m_char['L'] = m_char['l'];
		m_char['M'] = m_char['m'];
		m_char['N'] = m_char['n'];
		m_char['O'] = m_char['o'];
		m_char['P'] = m_char['p'];
		m_char['Q'] = m_char['q'];
		m_char['R'] = m_char['r'];
		m_char['S'] = m_char['s'];
		m_char['T'] = m_char['t'];
		m_char['U'] = m_char['u'];
		m_char['V'] = m_char['v'];
		m_char['W'] = m_char['w'];
		m_char['X'] = m_char['x'];
		m_char['Y'] = m_char['y'];
		m_char['Z'] = m_char['z'];
	}
}


