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

[[nodiscard]] bool modern_isdigit(wchar_t ch) modern_except_state;
[[nodiscard]] int32_t modern_todigit(wchar_t ch) modern_except_state;

class modern_string
{
	friend class modern_string_view;
	mutable modern_shared<class modern_array<wchar_t>> m_string;
public:
	modern_string();
	modern_string(modern_string& string);
	modern_string(const wchar_t* text);
	modern_string(const wchar_t* text_begin, const wchar_t* text_end);
	modern_string(const char* text);
	modern_string(const size_t number);
	modern_string(const int32_t number);
	modern_string(const int32_t num1, wchar_t* text, int32_t num2);
	modern_string(const uint32_t number);
	explicit modern_string(const char character);
	modern_string(modern_exception& exception);
	~modern_string();

	[[nodiscard]] wchar_t* const c_wstr() const modern_except_state;
	[[nodiscard]] char* const c_str() const modern_except_state;
	[[nodiscard]] 
	[[nodiscard]] size_t size() const modern_except_state;
	[[nodiscard]] int32_t to_int32() modern_except_state;
	[[nodiscard]] float to_float() modern_except_state;
	[[nodiscard]] bool to_bool() modern_except_state;

	[[nodiscard]] static modern_pair<modern_string, modern_string>& SplitString(const wchar_t* string, wchar_t token);

	      class modern_string& operator= (      class modern_string& string);
	const class modern_string& operator= (const class modern_string& string);
	modern_string& operator= (const wchar_t* string);

	modern_string operator+ (modern_string& string);

	[[nodiscard]] const size_t find_last_of(const wchar_t character) const modern_except_state;

	void push_back(const wchar_t element);
	void push_back(const char element);
	void pop_front();
	wchar_t*& data();
	void resize(size_t size);
	void load(const char* text);

private:

	void push_zero() const modern_except_state;

};


