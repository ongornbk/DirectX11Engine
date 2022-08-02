/*
Copyright(C) < 02.06.2020 > ongornbk@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE  ongornbk@gmail.com BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the ongornbk@gmail.com shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the ongornk@gmail.com.

modern is a trademark of ongornbk@gmail.com.
*/

#pragma once
#include "modern_def.h"
#include "modern_array.h"
#include "modern_shared.h"
#include "modern_pair.h"
#include "modern_weak.h"

class modern_exception;

[[nodiscard]] bool modern_isdigit(char ch) modern_except_state;
[[nodiscard]] int32_t modern_todigit(char ch) modern_except_state;

class modern_cstring
{
	modern_shared<modern_array<char>> m_string;
public:
	modern_cstring();
	modern_cstring(modern_cstring& string);
	modern_cstring(const char* text_begin,const char* text_end);
	modern_cstring(const char* text);
	modern_cstring(const char* text, const size_t number);
	modern_cstring(const size_t number);
	modern_cstring(const int32_t number);
	modern_cstring(const uint32_t number);
	explicit modern_cstring(const char character);
	modern_cstring(modern_exception& exception);
	~modern_cstring();

	[[nodiscard]] const wchar_t* c_wstr() const modern_except_state;
	[[nodiscard]] const char* c_str() const modern_except_state;
	[[nodiscard]]
	[[nodiscard]] size_t size() const modern_except_state;
	[[nodiscard]] int32_t to_int32() modern_except_state;
	[[nodiscard]] float to_float() modern_except_state;
	[[nodiscard]] bool to_bool() modern_except_state;

	[[nodiscard]] static modern_pair<modern_cstring, modern_cstring>& SplitString(const char* string, char token);

	modern_cstring& operator= (modern_cstring& string);
	modern_cstring& operator= (const char* string);

	modern_cstring operator+ (modern_cstring& string);

	void push_back(const wchar_t element);
	void push_back(const char element);
	void pop_front();
	char*& data();
	void resize(size_t size);
	void load(const char* text);

private:

	void push_zero() const modern_except_state;

};