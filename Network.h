#pragma once
#include <cstdint>

class Network
{
public:
	static bool Initialize();
	static void Release();
	static bool StartServer(uint16_t port);
protected:
	Network();
	~Network();
};

