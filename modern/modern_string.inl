/*
Copyright(C) < 10.16.2022 > ongornbk@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE  ongornbk@gmail.com BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the ongornbk@gmail.com shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the ongornk@gmail.com.

modern is a trademark of ongornbk@gmail.com.
*/

#include "modern_string.h"

const inline bool modern_isdigit(const wchar_t ch)
{
	return (ch >= L'0' && ch <= L'9');
}

const inline int8_t modern_toint8(const wchar_t ch)
{
	return (int8_t)(ch - L'0');
}

const inline int16_t modern_toint16(const wchar_t ch)
{
	return (int16_t)(ch - L'0');
}

const inline int32_t modern_toint32(const wchar_t ch)
{
	return (int32_t)(ch - L'0');
}

const inline int64_t modern_toint64(const wchar_t ch)
{
	return (int64_t)(ch - L'0');
}

const inline uint8_t modern_touint8(const wchar_t ch)
{
	return (uint8_t)(ch - L'0');
}

const inline uint16_t modern_touint16(const wchar_t ch)
{
	return (uint16_t)(ch - L'0');
}

const inline uint32_t modern_touint32(const wchar_t ch)
{
	return (uint32_t)(ch - L'0');
}

const inline uint64_t modern_touint64(const wchar_t ch)
{
	return (uint64_t)(ch - L'0');
}