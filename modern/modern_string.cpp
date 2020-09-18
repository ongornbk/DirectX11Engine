#include "modern_string.h"
#include "modern_exception.h"
#include "modern_math.h"

constexpr wchar_t cs_number[10] = { '0','1','2','3','4','5','6','7','8','9' };

modern_string::modern_string()
{
	m_string.make_shared(new modern_array<wchar_t>());
	m_string->push_back('\0');
}

modern_string::modern_string(modern_string& string)
{
	m_string.make_shared(new modern_array<wchar_t>());
	m_string->reserve(string.size() + 1);
	m_string->resize(string.size());
#pragma warning(disable : 4996)
	wcscpy(m_string->data(), string.c_wstr());
}

modern_string::modern_string(const wchar_t* text)
{
	m_string.make_shared(new modern_array<wchar_t>());
	m_string->reserve(wcslen(text)+1);
	m_string->resize(wcslen(text)+1);
#pragma warning(disable : 4996)
	wcscpy(m_string->data(), text);
}

modern_string::modern_string(const wchar_t* text_begin, const wchar_t* text_end)
{
	m_string.make_shared(new modern_array<wchar_t>());
	m_string->reserve(text_end - text_begin + 1);
	m_string->resize(text_end - text_begin + 1);
	auto i = text_begin;
	for (i;i < text_end; i++)
	{
		push_back(*i);
	}
	if (*i != L'\0')
		push_back(L'\0');
}

modern_string::modern_string(const char* text)
{
	m_string.make_shared(new modern_array<wchar_t>());
	m_string->reserve(strlen(text) + 1);
	m_string->resize(strlen(text) + 1);
#pragma warning(disable : 4996)
	mbstowcs(m_string->data(), text, strlen(text));
}

modern_string::modern_string(const size_t number)
{
	m_string.make_shared(new modern_array<wchar_t>());
	
	size_t temp = number;

	if (number == 0)
		m_string->push_back('0'); 

	while (temp > 0)
	{
		m_string->push_back(cs_number[temp % 10u]);
		temp /= 10u;
	}
	m_string->reverse();
	m_string->push_back('\0');
}

modern_string::modern_string(const int32_t number)
{
	m_string.make_shared(new modern_array<wchar_t>());

	bool flag = false;

	if (number < 0)
		flag = true;

	if (number == 0)
		m_string->push_back('0');

	int32_t temp = modern_abs(number);
	while (temp > 0)
	{
		m_string->push_back(cs_number[temp % 10]);
		temp /= 10;
	}

	if (flag)
		m_string->push_back('-');

	m_string->reverse();
	m_string->push_back('\0');
}

modern_string::modern_string(const uint32_t number)
{
	m_string.make_shared(new modern_array<wchar_t>());

	if (number == 0u)
		m_string->push_back('0');

	uint32_t temp = number;

	while (temp > 0u)
	{
		m_string->push_back(cs_number[temp % 10u]);
		temp /= 10u;
	}



	m_string->reverse();
	m_string->push_back('\0');
}

modern_string::modern_string(const char character)
{
	wchar_t t;
	mbstowcs(&t, &character, 1);
	m_string->push_back(t);
}

modern_string::modern_string(modern_exception& exception)
{
	*this = exception.what();
}

modern_string::~modern_string()
{
}

const wchar_t* modern_string::c_wstr() const noexcept
{
	return m_string->data();
}

size_t modern_string::size() const noexcept
{
	return m_string->size();
}

modern_pair<modern_string, modern_string>& modern_string::SplitString(const wchar_t* string, wchar_t token)
{
	wchar_t currc;
	int32_t index = 0;
	do
	{
		currc = string[index];
		index++;
	} while (currc != token || currc != L'\0');

	modern_pair<modern_string, modern_string>* pair = 
		new modern_pair<modern_string, modern_string>
		(modern_string(string,string+index), modern_string(string+index));

	return *pair;
}


modern_string& modern_string::operator=(modern_string& string)
{
		if (this == &string)
			return *this;

		m_string.make_shared(string.m_string);

		return *this;
}

modern_string& modern_string::operator=(const wchar_t* string)
{
	m_string.make_shared(new modern_array<wchar_t>());
	m_string->reserve(wcslen(string) + 1);
	m_string->resize(wcslen(string) + 1);
#pragma warning(disable : 4996)
	wcscpy(m_string->data(), string);
	return *this;
}

#include <string>


modern_string modern_string::operator+(modern_string& string)
{
	return *this;
}

void modern_string::push_back(const wchar_t element)
{
	m_string->push_back(element);
}

void modern_string::push_back(const char element)
{
	wchar_t t;
	mbstowcs(&t, &element, 1);
	m_string->push_back(t);
}

wchar_t*& modern_string::data()
{
	return m_string->data();
}

void modern_string::resize(size_t size)
{
	m_string->resize(size);
}

void modern_string::load(const char* text)
{
	m_string.make_shared(new modern_array<wchar_t>());
	m_string->reserve(strlen(text) + 1);
	m_string->resize(strlen(text) + 1);
#pragma warning(disable : 4996)
	mbstowcs(m_string->data(), text, strlen(text));
}
