/*
Copyright(C) < 08.10.2022 > ongornbk@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE  ongornbk@gmail.com BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the ongornbk@gmail.com shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the ongornk@gmail.com.

modern is a trademark of ongornbk@gmail.com.
*/
#pragma once
#include "modern_def.h"
#include <xthreads.h>
#include <thread>

typedef _Thrd_t modern_thread_t;

class modern_thread
{
	modern_thread_t              m_thread;
    _beginthreadex_proc_type     m_foo;

    modern_thread() = delete;
public:
	modern_thread(_beginthreadex_proc_type foo) modern_except_state : m_thread{}, m_foo(foo) {}

    ~modern_thread() modern_except_state {
        if (joinable()) {
            _STD terminate();
        }
    }

    void start() {

        //_beginthread_proc_type;
        m_thread._Hnd = reinterpret_cast<void*>(_CSTD _beginthreadex(nullptr, 0ul, m_foo, nullptr, 0ul, &m_thread._Id));
        if (m_thread._Hnd)
        {

        }
        else {
            m_thread._Id = 0ul;
            std::_Throw_Cpp_error(std::_RESOURCE_UNAVAILABLE_TRY_AGAIN);
        }
    }

    _NODISCARD bool joinable() const modern_except_state
    {
        return m_thread._Id != 0ul;
    }

    void join() {
        if (!joinable()) {
            std::_Throw_Cpp_error(std::_INVALID_ARGUMENT);
        }

        if (m_thread._Id == _Thrd_id()) {
            std::_Throw_Cpp_error(std::_RESOURCE_DEADLOCK_WOULD_OCCUR);
        }

        if (_Thrd_join(m_thread, nullptr) != _Thrd_success) {
            std::_Throw_Cpp_error(std::_NO_SUCH_PROCESS);
        }

        m_thread = {};
    }

    const unsigned int get_id() const modern_thread_safe modern_except_state
    {
        return m_thread._Id;
    }

    
};