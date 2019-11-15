#pragma once
#include "Network.h"
#include "Enet.h"
#include "Server.h"
#include <vector>

namespace
{
	static Network* m_net = nullptr;
	static Server*  m_server = nullptr;
}

bool Network::Initialize()
{
	
//	if (enet_initialize() != 0)
//	{
	//	return false;
	//}
//	else
	//{
	//	m_net = new Network();
		return true;
	//}
}

void Network::Release()
{
	//enet_deinitialize();
	if (m_server)
	{
		delete m_server;
		m_server = nullptr;
	}
}

bool Network::StartServer(uint16_t port)
{
	if (m_server)
	{
		return false;
	}
		return m_server = new Server(port);
}

Network::Network()
{
}


Network::~Network()
{
}
