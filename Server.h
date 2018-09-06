#pragma once
#include "Enet.h"
#include <cstdint>

class Server
{
public:
	Server(uint16_t port);
	~Server();

	bool Initialize();
protected:
	ENetAddress address;
	ENetHost * server;
};

