#include "Options.h"

namespace
{
    static modern_handle m_activeOptions;
}

Options::Options()
{
    m_activeOptions.make_handle(this->m_object);
}

Options::~Options()
{
}

modern_handle const &Options::GetInstance()
{
    return m_activeOptions;
}

const int64_t Options::GetKey(const modern_cstring& name) volatile
{
    for (int64_t i = 0; i < OPTIONS_LENGTH; i++)
    {
        if (strcmp(m_optionsNames[i], name.c_str()))
        {

        }
        else
        {
            return i;
        }
    }
    return 0;
}
