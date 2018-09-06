#include "Server.h"



Server::Server(uint16_t port)
{
	address.host = ENET_HOST_ANY;
	address.port = port;
}


Server::~Server()
{
	enet_host_destroy(server);
}

bool Server::Initialize()
{
	server = enet_host_create(&address /* the address to bind the server host to */,
		32      /* allow up to 32 clients and/or outgoing connections */,
		2      /* allow up to 2 channels to be used, 0 and 1 */,
		0      /* assume any amount of incoming bandwidth */,
		0      /* assume any amount of outgoing bandwidth */);
	if (server == NULL)
	{
		return false;
	}
	return true;
}
