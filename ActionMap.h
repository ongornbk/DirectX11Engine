#pragma once
#include <string>
#include <functional>
#include <map>
#include <stack>
#include "IAction.h"

class ActionMap
{
	ActionMap();
	std::map< std::string, std::function<class IAction*(class ActionMap*)>> m_fooMap;
	std::stack<void*> m_stack;

public:

	~ActionMap();

	static class ActionMap* GetInstance();

	void AddAction(std::function<class IAction*(class ActionMap*)> foo, std::string name);

	std::function<class IAction* (class ActionMap*)> const GetAction(std::string);

	void* Pop();
	void Push(void* const ptr);
};

