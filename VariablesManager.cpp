#include "VariablesManager.h"




VariableInteger::VariableInteger()
{
}

VariableInteger::~VariableInteger()
{
}

int VariableInteger::GetInt(std::string name)
{
	if (m_integers.count(name))
	{
		return m_integers[name];
	}
	else return -1;
}

bool VariableInteger::PushInt(std::string name, int i)
{
	if (m_integers.count(name))
	{
		return false;
	}
	else
	{
		m_integers[name] = i;
		return true;
	}
}

bool VariableInteger::IncInt(std::string name)
{
	if (m_integers.count(name))
	{
		m_integers[name]++;
		return true;
	}
	else
	{
		return false;
	}
}

bool VariableInteger::DecInt(std::string name)
{
	if (m_integers.count(name))
	{
		m_integers[name]--;
		return true;
	}
	else
	{
		return false;
	}
}

bool VariableInteger::AddInt(std::string name, int i)
{
	if (m_integers.count(name))
	{
		m_integers[name]+=i;
		return true;
	}
	else
	{
		return false;
	}
}

bool VariableInteger::SubInt(std::string name, int i)
{
	if (m_integers.count(name))
	{
		m_integers[name]-=i;
		return true;
	}
	else
	{
		return false;
	}
}

bool VariableInteger::MulInt(std::string name, int i)
{
	if (m_integers.count(name))
	{
		m_integers[name]*=i;
		return true;
	}
	else
	{
		return false;
	}
}

bool VariableInteger::DivInt(std::string name, int i)
{
	if (m_integers.count(name)&&i)
	{
		m_integers[name]/=i;
		return true;
	}
	else
	{
		return false;
	}
}

VariableString::VariableString()
{
}

VariableString::~VariableString()
{
}

std::string VariableString::GetString(std::string name)
{
	if (m_strings.count(name))
	{
		return m_strings[name];
	}
	else return std::string("No such variable!"+name);
}

bool VariableString::PushString(std::string name, std::string value)
{
	if (m_strings.count(name))
	{
		return false;
	}
	else
	{
		m_strings[name] = value;
		return true;
	}
}

bool VariableString::MergeString(std::string name, std::string value)
{
	if (m_strings.count(name))
	{
		m_strings[name] = (m_strings[name] + value);
		return true;
	}
	else
	{
		return false;
	}
}

VariablesManager::VariablesManager() : VariableInteger(),VariableString(),VariableUnit()
{
}

VariablesManager::~VariablesManager()
{
	m_strings.clear();
	m_integers.clear();
	m_units.clear();
}

VariableUnit::VariableUnit()
{
}

VariableUnit::~VariableUnit()
{
}

Unit * VariableUnit::GetUnit(std::string name)
{
	if (m_units.count(name))
	{
		return m_units[name];
	}
	else return nullptr;
}

bool VariableUnit::PushUnit(std::string name, Unit * i)
{
	if (m_units.count(name))
	{
		return false;
	}
	else
	{
		if (i)
		{
			m_units[name] = i;
			return true;
		}
		else
		{
			return false;
		}
	}
}

