#pragma once
#include <mysql.h>
#include "modern/modern_database_connection_details.h"



class MySQLManager
{
	MYSQL* m_connection{};
public:
	const modern_Boolean initialize(struct modern_database_connection_details details);

};

