#pragma once
#include "modern_def.h"
#include "modern_class.h"
#include "modern_guard_status.h"


/*
Copyright(C) < 02.06.2020 > ongornbk@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE  ongornbk@gmail.com BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the ongornbk@gmail.com shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the ongornk@gmail.com.

modern is a trademark of ongornbk@gmail.com.
*/


class modern_shared_guard
{
	volatile std::atomic<int64_t>* m_lock;

public:

	modern_shared_guard() = delete;
	modern_shared_guard(class modern_shared_guard& guard) = delete;
	_stdcall modern_shared_guard(struct modern_class* const object) modern_except_state;
	_stdcall modern_shared_guard(volatile struct modern_class* const object) modern_except_state;
	_stdcall modern_shared_guard(const struct modern_class* const object) modern_except_state;
	_stdcall modern_shared_guard(std::atomic<int64_t>& lock) modern_except_state;
	_stdcall ~modern_shared_guard() modern_except_state;
};

