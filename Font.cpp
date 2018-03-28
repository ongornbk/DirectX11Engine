#include "Font.h"
#include <fstream>
#include "ResourceManager.h"

Font::Font()
{
	m_font = NULL;
	m_texture = NULL;
}


Font::~Font()
{
	if (m_font)
	{
		delete[] m_font;
		m_font = NULL;
	}
	if (m_texture)
	{
		delete m_texture;
		m_texture = NULL;
	}
}

Font::Font(const Font &other)
{
}

bool Font::Initialize(ID3D11Device *device, char * fontfilename,WCHAR*texturefilename)
{
	bool result;

	result = LoadFontData(fontfilename);
	if (FAILED(result))
	{
		return false;
	}

	result = LoadTexture(device, texturefilename);
	if (!result)
	{
		return false;
	}

	return true;


}

void Font::Shutdown()
{
}

ID3D11ShaderResourceView * Font::GetTexture()
{
	return m_texture->GetTexture();
}

void Font::BuildVertexArray(void *vertices, char *sentence, float drawX, float drawY)
{
	VertexType* vertexPtr;
	int numLetters, index, i, letter;

	vertexPtr = (VertexType*)vertices;

	numLetters = (int)strlen(sentence);

	index = 0;

		for (i = 0; i<numLetters; i++)
		{
			letter = ((int)sentence[i]) - 32;

			if (letter == 0)
			{
				drawX = drawX + 3.0f;
			}
			else
			{
				// First triangle in quad.
				vertexPtr[index].position = XMVectorSet(drawX, drawY, 0.0f,0.0f);
				vertexPtr[index].texture = XMVectorSet(m_font[letter].left, 0.0f,0.0f,0.0f);
				index++;

				vertexPtr[index].position = XMVectorSet((drawX + m_font[letter].size), (drawY - 16), 0.0f,0.0f);  // Bottom right.
				vertexPtr[index].texture = XMVectorSet(m_font[letter].right, 1.0f,0.0f,0.0f);
				index++;

				vertexPtr[index].position = XMVectorSet(drawX, (drawY - 16), 0.0f,0.0f);  // Bottom left.
				vertexPtr[index].texture = XMVectorSet(m_font[letter].left, 1.0f,0.0f,0.0f);
				index++;

				// Second triangle in quad.
				vertexPtr[index].position = XMVectorSet(drawX, drawY, 0.0f,0.0f);  // Top left.
				vertexPtr[index].texture = XMVectorSet(m_font[letter].left, 0.0f,0.0f,0.0f);
				index++;

				vertexPtr[index].position = XMVectorSet(drawX + m_font[letter].size, drawY, 0.0f,0.0f);  // Top right.
				vertexPtr[index].texture = XMVectorSet(m_font[letter].right, 0.0f,0.0f,0.0f);
				index++;

				vertexPtr[index].position = XMVectorSet((drawX + m_font[letter].size), (drawY - 16), 0.0f,0.0f);  // Bottom right.
				vertexPtr[index].texture = XMVectorSet(m_font[letter].right, 1.0f,0.0f,0.0f);
				index++;

				// Update the x location for drawing by the size of the letter and one pixel.
				drawX = drawX + m_font[letter].size + 1.0f;
			}
		}

	return;
}

bool Font::LoadFontData(char* filename)
{
	ifstream fin;
	int i;
	char temp;

	m_font = new FontType[95];
	if (!m_font)
	{
		return false;
	}

		fin.open(filename);
	if (fin.fail())
	{
		return false;
	}

	for (i = 0; i<95; i++)
	{
		fin.get(temp);
		while (temp != ' ')
		{
			fin.get(temp);
		}
		fin.get(temp);
		while (temp != ' ')
		{
			fin.get(temp);
		}

		fin >> m_font[i].left;
		fin >> m_font[i].right;
		fin >> m_font[i].size;
	}


	fin.close();

	return true;
}



bool Font::LoadTexture(ID3D11Device *device, WCHAR *filename)
{
	bool result;


	// Create the texture object.
	m_texture = new Texture();


	// Initialize the texture object.
	result = m_texture->Initialize(device, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

