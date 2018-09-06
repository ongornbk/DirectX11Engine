#pragma once
#include <thread>
#include <atomic>
#include <map>

class Connection
{
public:
	Connection();
	~Connection();

	void Run();
	void Release();
protected:
	std::thread* m_thread;


};

