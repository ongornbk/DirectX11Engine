#pragma once

#include <modern__.h>

class TaskPrintlnString :
    public modern_task
{
    enum MODERN_CONSOLE_TEXT_COLOR m_color;
    class modern_string m_str;
public:
    TaskPrintlnString(const class modern_string& str,const enum MODERN_CONSOLE_TEXT_COLOR color = MODERN_CONSOLE_TEXT_COLOR::WHITE);
    ~TaskPrintlnString();

    void execute() override;
};

