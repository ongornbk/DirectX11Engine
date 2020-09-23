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

[[nodiscard]] bool modern_isdigit(wchar_t ch) noexcept;
[[nodiscard]] int32_t modern_todigit(wchar_t ch) noexcept;

class modern_string
{
	modern_shared<modern_array<wchar_t>> m_string;
public:
	modern_string();
	modern_string(modern_string& string);
	modern_string(const wchar_t* text);
	modern_string(const wchar_t* text_begin, const wchar_t* text_end);
	modern_string(const char* text);
	modern_string(const size_t number);
	modern_string(const int32_t number);
	modern_string(const uint32_t number);
	explicit modern_string(const char character);
	modern_string(modern_exception& exception);
	~modern_string();

	[[nodiscard]] const wchar_t* c_wstr() const noexcept;
	[[nodiscard]] const _bstr_t& c_str() const noexcept;
	[[nodiscard]] size_t size() const noexcept;
	[[nodiscard]] int32_t to_int32() noexcept;
	[[nodiscard]] static modern_pair<modern_string, modern_string>& SplitString(const wchar_t* string, wchar_t token);

	modern_string& operator= (modern_string& string);
	modern_string& operator= (const wchar_t* string);

	modern_string operator+ (modern_string& string);

	void push_back(const wchar_t element);
	void push_back(const char element);
	wchar_t*& data();
	void resize(size_t size);
	void load(const char* text);

};

