#include "ResourceFont.h"



ResourceFont::ResourceFont()
{
	m_font = NULL;
}


ResourceFont::~ResourceFont()
{
	if (m_font)
	{
		delete m_font;
		m_font = NULL;
	}
}

bool ResourceFont::Load(ID3D11Device * device, WCHAR * fontFileName)
{
	//m_font = new Font();
	//if (!m_font->Initialize(device, fontFileName))
//	{
	//	delete m_font;
	//	m_font = NULL;
	//	return false;
//	}
	//return true;
}

Font * ResourceFont::GetFont()
{
	return nullptr;
}

string ResourceFont::GetName()
{
	return string();
}


