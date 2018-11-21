#pragma once
#include <rapidxml.hpp>
#include <string>


class XMLParser
{
public:

	XMLParser();
	~XMLParser();

	

	void Parse(std::string path);
	void Release();

private:

	

	rapidxml::xml_document<> m_document;
};

