#pragma once
#include "modern_def.h"
#include "modern_string.h"

class modern_exception
{
    modern_string m_data;

public:

    modern_exception() noexcept : m_data()
    {

    }

    virtual ~modern_exception() noexcept
    {

    }

    explicit modern_exception(wchar_t const* const message) noexcept : m_data(message)
    {
    }

    modern_exception(modern_exception& other) noexcept
    {
        m_data = other.m_data;
    }

    modern_exception& operator=(modern_exception& other) noexcept
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