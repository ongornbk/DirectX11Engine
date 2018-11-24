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

VariablesManager::VariablesManager() : VariableInteger(),VariableString(),VariableUnit(),VariableBoolean(),VariablePoint(),VariableReal()
{
}

VariablesManager::~VariablesManager()
{
	m_strings.clear();
	m_integers.clear();
	m_units.clear();
	m_bools.clear();
	m_points.clear();
	m_reals.clear();
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

bool VariableUnit::EraseUnit(std::string name)
{
	if (m_units.count(name))
	{
		m_units.erase(name);
		return true;
	}
	else return false;
}

VariableBoolean::VariableBoolean()
{
}

VariableBoolean::~VariableBoolean()
{
}

int8_t VariableBoolean::GetBoolean(std::string name)
{
	if (m_bools.count(name))
	{
		return m_bools[name];
	}
	else return -1;
}

bool VariableBoolean::PushBoolean(std::string name, bool i)
{
	if (m_bools.count(name))
	{
		return false;
	}
	else
	{
		if (i)
		{
			m_bools[name] = i;
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool VariableBoolean::EraseBoolean(std::string name)
{
	if (m_bools.count(name))
	{
		m_bools.erase(name);
		return true;
	}
	else return false;
}

bool VariableBoolean::NegateBoolean(std::string name)
{
	if (m_bools.count(name))
	{
		if (m_bools[name])
			m_bools[name] = false;
		else
			m_bools[name] = true;
		return true;
	}
	else return false;
}

VariablePoint::VariablePoint()
{
}

VariablePoint::~VariablePoint()
{
}

XMFLOAT3 VariablePoint::GetPoint(std::string name)
{
	if (m_points.count(name))
	{
		return m_points[name];
	}
	else XMFLOAT3(0.0f, 0.0f, 0.0f);
}

bool VariablePoint::PushPoint(std::string name, XMFLOAT3 i)
{
	if (m_points.count(name))
	{
		return false;
	}
	else
	{
			m_points[name] = i;
			return true;
	}
}

bool VariablePoint::ErasePoint(std::string name)
{
	if (m_points.count(name))
	{
		m_points.erase(name);
		return true;
	}
	else return false;
}

VariableReal::VariableReal()
{
}

VariableReal::~VariableReal()
{
}

float VariableReal::GetReal(std::string name)
{
	if (m_reals.count(name))
	{
		return m_reals[name];
	}
	else return -1.0f;
}

bool VariableReal::PushReal(std::string name, float i)
{
	if (m_reals.count(name))
	{
		return false;
	}
	else
	{
		m_reals[name] = i;
		return true;
	}
}

bool VariableReal::IncReal(std::string name)
{
	if (m_reals.count(name))
	{
		return false;
	}
	else
	{
		m_reals[name]++;
		return true;
	}
}

bool VariableReal::DecReal(std::string name)
{
	if (m_reals.count(name))
	{
		return false;
	}
	else
	{
		m_reals[name]--;
		return true;
	}
}

bool VariableReal::AddReal(std::string name, float i)
{
	if (m_reals.count(name))
	{
		return false;
	}
	else
	{
		m_reals[name] += i;
		return true;
	}
}

bool VariableReal::SubReal(std::string name, float i)
{
	if (m_reals.count(name))
	{
		return false;
	}
	else
	{
		m_reals[name] -= i;
		return true;
	}
}

bool VariableReal::MulReal(std::string name, float i)
{
	if (m_reals.count(name))
	{
		return false;
	}
	else
	{
		m_reals[name] *= i;
		return true;
	}
}

bool VariableReal::DivReal(std::string name, float i)
{
	if (m_reals.count(name) && i)
	{
		m_reals[name] /= i;
		return true;
	}
	else
	{
		return false;
	}
}
