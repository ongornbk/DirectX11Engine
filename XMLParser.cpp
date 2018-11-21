#include "XMLParser.h"



XMLParser::XMLParser()
{
}


XMLParser::~XMLParser()
{
}



void XMLParser::Parse(std::string path)
{
	char* wc = (char*)malloc(sizeof(char)*path.length());
	memcpy(wc, path.c_str(), path.size());
	m_document.parse<0>(wc);

	free(wc);
}

void XMLParser::Release()
{
	delete(this);
}
