#include "modern_cstring.h"
#include "modern_exception.h"
#include "modern_math.h"
#include <iostream>



constexpr char cs_number[10] = { '0','1','2','3','4','5','6','7','8','9' };

modern_cstring::modern_cstring()
{
	m_string.make_shared(new class modern_array<char>());
	push_zero();
}

modern_cstring::modern_cstring(class modern_cstring& string)
{
	m_string.make_shared(new modern_array<char>());
	m_string->reserve(string.size() + 1);
	m_string->resize(string.size());
#pragma warning(disable : 4996)
	//wcscpy(m_string->data(), string.c_wstr());
	strcpy(m_string->data(), string.c_str());
}

modern_cstring::modern_cstring(const char* text_begin, const char* text_end)
{

	m_string.make_shared(new modern_array<char>());
	m_string->reserve(text_end - text_begin + 1);
	m_string->resize(text_end - text_begin + 1);
	auto i = text_begin;
	for (i; i < text_end; i++)
	{
		push_back(*i);
	}
	if (*i != '\0')
		push_zero();
}

modern_cstring::modern_cstring(const char* text)
{
	m_string.make_shared(new modern_array<char>());
	m_string->reserve(strlen(text) + 1);
	m_string->resize(strlen(text) + 1);
#pragma warning(disable : 4996)
	//mbstowcs(m_string->data(), text, strlen(text));
	strncpy(m_string->data(), text, strlen(text));
}

modern_cstring::modern_cstring(const char* text, const size_t number)
{
	m_string.make_shared(new modern_array<char>());

	size_t temp = number;
	const size_t strl = strlen(text);

	

	if (number == 0)
		m_string->push_back('0');

	while (temp > 0)
	{
		m_string->push_back(cs_number[temp % 10u]);
		temp /= 10u;
	}

	for (size_t i = 1; i <= strl; i++)
	{
		m_string->push_back(text[strl -i]);
	}

	m_string->reverse();
	m_string->push_back('\0');
}

modern_cstring::modern_cstring(const size_t number)
{
	m_string.make_shared(new modern_array<char>());

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

modern_cstring::modern_cstring(const int32_t number)
{
	m_string.make_shared(new modern_array<char>());

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

modern_cstring::modern_cstring(const uint32_t number)
{
	m_string.make_shared(new modern_array<char>());

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

modern_cstring::modern_cstring(const char character)
{
	//wchar_t t;
	//mbstowcs(&t, &character, 1);
	m_string->push_back(character);
}

modern_cstring::modern_cstring(modern_exception& exception)
{
//	*this = exception.what();
}

modern_cstring::~modern_cstring()
{
}

const wchar_t* modern_cstring::c_wstr() const modern_except_state
{
	//return m_string->data();
	return nullptr;
}

const char* modern_cstring::c_str() const modern_except_state
{
	//return _bstr_t(m_string->data());
	return m_string->data();
}

const size_t modern_cstring::size() const modern_except_state
{
	return m_string->size();
}

const int32_t modern_cstring::to_int32() modern_except_state
{
	modern_array<int32_t> digits;
	int32_t value = 0;
	//modern_shared<modern_array<char>> base;

	//base.make_shared(m_string);

	for (auto ch : *m_string)
	{
		if (modern_isdigit(ch))
			digits.push_back(modern_toint32(ch));
	}

	for (int32_t i = 0l; i < digits.size(); i++)
	{
		int32_t mult = (int32_t)digits.size() - i;
		int32_t val10 = digits[i];
		for (int32_t ii = 0l; ii < mult - 1; ii++)
		{
			val10 *= 10l;
		}
		value += val10;
	}

	if (m_string->at(0ull) modern_equal '-')
		return value * (-1l);
	return value;
}

const uint32_t modern_cstring::to_uint32()
{
	modern_array<uint32_t> digits;
	uint32_t value = 0ul;

	for (auto ch : *m_string)
	{
		if (modern_isdigit(ch))
			digits.push_back(modern_touint32(ch));
	}

	for (int32_t i = 0l; i < digits.size(); i++)
	{
		int32_t mult = (int32_t)digits.size() - i;
		int32_t val10 = digits[i];
		for (int32_t ii = 0l; ii < mult - 1; ii++)
		{
			val10 *= 10ul;
		}
		value += val10;
	}

	return value;
}

float modern_cstring::to_float() modern_except_state
{
	float result = 0.f;
	float negative = 1.f;
	if (m_string->at(0) == '-')
	{
		negative = -1.f;
		pop_front();
	}

	//modern_pair<modern_string, modern_string> split = SplitString(m_string->data(), L'.');

	//result += (float)split.first.to_int32();

	//float fres = (float)split.second.to_int32();
	//fres /= modern_pow(10.f, (int32_t)split.second.size());

	//return (result + fres) * negative;

	return 1.0f;
}

bool modern_cstring::to_bool() modern_except_state
{
	if (m_string->at(0) == 't' || m_string->at(0) == 'T' || m_string->at(0) == '1')
	{
		return true;
	}
	else return false;
}

modern_pair<modern_cstring, modern_cstring>& modern_cstring::SplitString(const char* string, char token)
{
	int32_t index = 0;
	do
	{
		index++;
	} while (*(string + index) != token);

	modern_pair<modern_cstring, modern_cstring>* pair =
		new modern_pair<modern_cstring, modern_cstring>
		(modern_cstring(string, string + index), modern_cstring(string + index));


	return *pair;
}


modern_cstring& modern_cstring::operator=(modern_cstring& string)
{
	if (this == &string)
		return *this;

	m_string.make_shared(string.m_string);

	return *this;
}

modern_cstring& modern_cstring::operator=(const char* string)
{
	m_string.make_shared(new class modern_array<char>());
	for (int64_t i = 0; i < 100ll; i++)
	{
		if (string[i] == '\0')
			goto END;
		m_string->push_back(string[i]);

	}
END:
	push_zero();

	return *this;
}



#include <string>


modern_cstring modern_cstring::operator+(modern_cstring& string)
{
	return *this;
}

void modern_cstring::push_back(const wchar_t element)
{
	//m_string->push_back(element);
}

void modern_cstring::push_back(const char element)
{
	//wchar_t t;
	//mbstowcs(&t, &element, 1);
	m_string->push_back(element);
}

void modern_cstring::pop_front()
{
	if (size())
		m_string->remove(0ull);
}

char*& modern_cstring::data()
{
	return m_string->data();
}

void modern_cstring::resize(size_t size)
{
	m_string->resize(size);
}

void modern_cstring::load(const char* text)
{
	m_string.make_shared(new modern_array<char>());
	m_string->reserve(strlen(text) + 2ull);
	m_string->resize(strlen(text) + 1ull);
#pragma warning(disable : 4996)
	//mbstowcs(m_string->data(), text, strlen(text));
	strncpy(m_string->data(), text, strlen(text));
}

void modern_cstring::push_zero() const modern_except_state
{
	m_string->push_back('\0');
}

const bool modern_isdigit(const char ch) modern_except_state
{
	return (ch >= L'0' && ch <= L'9');
}

const int8_t modern_toint8(const char ch) modern_except_state
{
	return (int8_t)(ch - '0');
}

const int16_t modern_toint16(const char ch) modern_except_state
{
	return (int16_t)(ch - '0');
}

const int32_t modern_toint32(const char ch) modern_except_state
{
	return (int32_t)(ch - '0');
}

const int64_t modern_toint64(const char ch) modern_except_state
{
	return (int64_t)(ch - '0');
}

const uint8_t modern_touint8(const char ch) modern_except_state
{
	return (uint8_t)(ch - '0');
}

const uint16_t modern_touint16(const char ch) modern_except_state
{
	return (uint16_t)(ch - '0');
}

const uint32_t modern_touint32(const char ch) modern_except_state
{
	return (uint32_t)(ch - '0');
}

const uint64_t modern_touint64(const char ch) modern_except_state
{
	return (uint64_t)(ch - '0');
}