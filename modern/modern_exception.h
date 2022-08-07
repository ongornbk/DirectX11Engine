#pragma once
#include "modern_def.h"
#include "modern_string.h"

class modern_exception
{
    modern_string m_data;

public:

    modern_exception() modern_except_state : m_data()
    {

    }

    virtual ~modern_exception() modern_except_state
    {

    }

    explicit modern_exception(wchar_t const* const message) modern_except_state
    {
        m_data = message;
    }

    explicit modern_exception(const class modern_string& message) modern_except_state
    {
        m_data = message;
    }

    modern_exception(modern_exception& other) modern_except_state
    {
        m_data = other.m_data;
    }

    modern_exception& operator=(modern_exception& other) modern_except_state
    {
        if (this == &other)
        {
            return *this;
        }

        m_data = other.m_data;
        return *this;
    }

    [[nodiscard]] virtual modern_string& what()
    {
        return m_data;
    }
};