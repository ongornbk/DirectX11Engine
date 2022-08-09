#include "modern_string.h"
#include "modern_exception.h"
#include "modern_math.h"
#include <iostream>
#include <string>


constexpr wchar_t cs_number[10ll] = { L'0',L'1',L'2',L'3',L'4',L'5',L'6',L'7',L'8',L'9' };

modern_string::modern_string()
{
	m_string.make_shared(new class modern_array<wchar_t>());
	push_zero();
}

modern_string::modern_string(class modern_string& string)
{
	m_string.make_shared(new class modern_array<wchar_t>());
	m_string->reserve(string.size() + 1);
	m_string->resize(string.size());
#pragma warning(disable : 4996)
	wcscpy(m_string->data(), string.c_wstr());
}

modern_string::modern_string(const wchar_t* text)
{
	m_string.make_shared(new class modern_array<wchar_t>());
	for (int64_t i = 0ll; i < 100ll; i++)
	{
		if (text[i] == L'\0')
			goto END;
		m_string->push_back(text[i]);

	}
END:
	push_zero();
}

modern_string::modern_string(const wchar_t* text_begin, const wchar_t* text_end)
{

	m_string.make_shared(new class modern_array<wchar_t>());
	m_string->reserve(text_end - text_begin + 1ull);
	m_string->resize(text_end - text_begin + 1ull);
	auto i = text_begin;
	for (i;i < text_end; i++)
	{
		push_back(*i);
	}
	if (*i != L'\0')
		push_zero();
}

modern_string::modern_string(const char* text)
{
	m_string.make_shared(new class modern_array<wchar_t>());
	m_string->reserve(strlen(text) + 1);
	for (int64_t i = 0ll; i < 100ll; i++)
	{
		if (text[i] == '\0')
			goto END;
		m_string->push_back(wchar_t());
		mbtowc(m_string->data() + i, text + i, 1);
	}
//#pragma warning(disable : 4996)
	//mbstowcs(m_string->data(), text, m_string->size());
	END:
	push_zero();
}

modern_string::modern_string(const size_t number)
{
	m_string.make_shared(new class modern_array<wchar_t>());

	if (number == 0ull)
	{
		m_string->push_back(L'0');
		goto END;
	}
	
	size_t temp = number;

	//if (number == 0ull)
		//push_zero();

	while (temp > 0ull)
	{
		m_string->push_back(cs_number[temp % 10ull]);
		temp /= 10ull;
	}
	m_string->reverse();

END:

	push_zero();
}

modern_string::modern_string(const int32_t number)
{
	m_string.make_shared(new class modern_array<wchar_t>());

	bool flag = false;

	if (number < 0ull)
		flag = true;

	if (number == 0ull)
		push_zero();

	int32_t temp = modern_abs(number);
	while (temp > 0ull)
	{
		m_string->push_back(cs_number[temp % 10ull]);
		temp /= 10ull;
	}

	if (flag)
		m_string->push_back(L'-');

	m_string->reverse();
	push_zero();
}

modern_string::modern_string(const int32_t num1, wchar_t* text, int32_t num2)
{
	m_string.make_shared(new class modern_array<wchar_t>());

	modern_string num1t(num1);
	modern_string num2t(num2);

	wchar_t*& t1 = num1t.data();
	wchar_t*& t2 = num2t.data();

	for (int64_t i = 0; i < 100; i++)
	{
		if (t1[i] == '\0')
			goto END1;
		m_string->push_back(t1[i]);

	}
END1:

	for (int64_t i = 0; i < 100; i++)
	{
		if (text[i] == '\0')
			goto END2;
		m_string->push_back(text[i]);

	}
END2:
	for (int64_t i = 0; i < 100; i++)
	{
		if (t2[i] == '\0')
			goto END3;
		m_string->push_back(t2[i]);

	}
END3:
	push_zero();
}

modern_string::modern_string(const uint32_t number)
{
	m_string.make_shared(new class modern_array<wchar_t>());

	if (number == 0u)
		m_string->push_back('0');

	uint32_t temp = number;

	while (temp > 0u)
	{
		m_string->push_back(cs_number[temp % 10u]);
		temp /= 10u;
	}



	m_string->reverse();
	push_zero();
}

modern_string::modern_string(const char character)
{
	wchar_t t;
	mbstowcs(&t, &character, 1);
	m_string->push_back(t);
}

modern_string::modern_string(class modern_exception& exception)
{
	*this = exception.what();
}

modern_string::~modern_string()
{
}

wchar_t* const modern_string::c_wstr() const modern_except_state
{
	return m_string->data();
}

char* const modern_string::c_str() const modern_except_state
{
	return _bstr_t(m_string->data());
}

size_t modern_string::size() const modern_except_state
{
	return m_string->size();
}

int32_t modern_string::to_int32() modern_except_state
{
	modern_array<int32_t> digits;
	modern_shared<modern_array<wchar_t>> base;

	base.make_shared(m_string);

	for (auto  ch : *base)
	{
		if (modern_isdigit(ch))
			digits.push_back(modern_todigit(ch));
	}
	int32_t value = 0;
	for (int32_t i = 0; i < digits.size(); i++)
	{
		int32_t mult = (int32_t)digits.size() - i;
		int32_t val10 = digits[i];
		for (int32_t ii = 0; ii < mult - 1; ii++)
		{
			val10 *= 10;
		}
		value += val10;
	}

	return value;
}

float modern_string::to_float() modern_except_state
{
	//float result = 0.f;
	//float negative = 1.f;
	//if (m_string->at(0) == L'-')
	//{
	//	negative = -1.f;
	//	pop_front();
	//}
	//
	////modern_pair<modern_string, modern_string> split = SplitString(m_string->data(), L'.');
	////
	////result += (float)split.first.to_int32();
	////
	////float fres = (float)split.second.to_int32();
	////fres /= modern_pow(10.f, (int32_t)split.second.size());
	////
	////return (result + fres) * negative;
	//
	//return 1.0f;

	return std::stof(m_string->data());
}

bool modern_string::to_bool() modern_except_state
{
	if (m_string->at(0) == L't' || m_string->at(0) == L'T' || m_string->at(0) == L'1')
	{
		return true;
	}
	else return false;
}

modern_pair<modern_string, modern_string>& modern_string::SplitString(const wchar_t* string, wchar_t token)
{
	int32_t index = 0;
	do
	{
		index++;
	} while (*(string + index) != token);

	modern_pair<modern_string, modern_string>* pair = 
		new modern_pair<modern_string, modern_string>
		(modern_string(string,string+index), modern_string(string+index));


	return *pair;
}


class modern_string& modern_string::operator=(class modern_string& string)
{
		if (this == &string)
			return *this;

		m_string.make_shared(string.m_string);

		return *this;
}

const class modern_string& modern_string::operator=(const class modern_string& string)
{
	if (this == &string)
		return *this;

	m_string.make_shared(string.m_string);

	return *this;
}

modern_string& modern_string::operator=(const wchar_t* string)
{
	m_string.make_shared(new class modern_array<wchar_t>());
	for (int64_t i = 0; i < 100ll; i++)
	{
		if (string[i] == L'\0')
			goto END;
		m_string->push_back(string[i]);

	}
END:
	push_zero();

	return *this;
}



#include <string>


modern_string modern_string::operator+(modern_string& string)
{
	return *this;
}

modern_string& modern_string::operator<<(modern_string& string)
{
	const size_t newsize = size() + string.size();
	m_string->reserve(newsize);
	m_string->resize(modern_max(m_string->size(), 1ull) - 1ull);
	for (size_t i = 0ull; i < string.size(); ++i)
	{
		m_string->push_back(string.at(i));
	}

	return *this;
}

const size_t modern_string::find_last_of(const wchar_t character) const modern_except_state
{
//	size_t n = 0ull;
//	int32_t i = size();
//	while (i)
//	{
//
//	}
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

void modern_string::pop_front()
{
	m_string->remove(0);
}

wchar_t*& modern_string::data()
{
	return m_string->data();
}

void modern_string::resize(size_t size)
{
	m_string->resize(size);
}

void modern_string::push_zero() const modern_except_state
{
	m_string->push_back(L'\0');
}

void modern_string::load(const char* text)
{
	m_string.make_shared(new modern_array<wchar_t>());
	m_string->reserve(strlen(text) + 1);
	m_string->resize(strlen(text) + 1);
#pragma warning(disable : 4996)
	mbstowcs(m_string->data(), text, strlen(text));
}

const wchar_t modern_string::at(const size_t index) const modern_except_state
{
	if (index < m_string->size())
		return (*m_string)[index];
	return L'\0';
}

bool modern_isdigit(wchar_t ch) modern_except_state
{
	return (ch >= L'0' && ch <= L'9');
}

int32_t modern_todigit(wchar_t ch) modern_except_state
{
	return ch - L'0';
}
