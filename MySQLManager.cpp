#include "MySQLManager.h"
#include "SettingsC.h"
#include "IPP.h"

#pragma comment(lib,"libmysql.lib")


const modern_Boolean MySQLManager::initialize(modern_database_connection_details details)
{
    m_connection = mysql_init(nullptr);

    if(!mysql_real_connect(
        m_connection,
        details.server.c_str(),
        details.user.c_str(),
        details.password.c_str(),
        details.database.c_str(),
        Settings::GetDatabasePort().to_uint32(),
        0,
        0
    ))
    {
        ipp::Console::Println("MYSQL:: ERROR-> ",mysql_error(m_connection), MODERN_CONSOLE_TEXT_COLOR::RED);
        return modern_true;
    }

    ipp::Console::Println("MYSQL:: Connectted to -> ", details.server, MODERN_CONSOLE_TEXT_COLOR::DARKGREEN);


    return modern_false;
}

