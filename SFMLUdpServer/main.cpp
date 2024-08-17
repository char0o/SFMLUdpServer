#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "Globals.h"
#include "Client.h"
#include "ClientList.h"
#include "Packets.hpp"
#include "NetManager.h"
#include "Entity.h"
#include "EntityList.h"
#include "EntityListPacket.h"
#include <iostream>
#include <thread>
#include <queue>
int main(int argc, char* argv[])
{
	sf::UdpSocket socket;
	socket.setBlocking(false);

	if (socket.bind(SERVER_PORT) != sf::Socket::Done)
	{
		std::cout << "Error while binding the socket" << std::endl;
		return -1;
	}
	sf::Clock clock;
	float timeAccumulator = 0.0f;
	sf::Time totalTime;
	bool quit = false;
	int ticks = 0;
	ClientList clientList;
	EntityList entityList;

	std::queue<NetCommand> commandQueue;

	while (!quit)
	{
		float dt = clock.restart().asSeconds();
		timeAccumulator += dt;

		while (timeAccumulator >= TICKRATIO)
		{	
			HandleCommands(commandQueue, entityList, ticks);
			Listen(socket, entityList, clientList);
			SendEntities(socket, entityList, clientList, ticks);
			entityList.Update(sf::seconds(TICKRATIO));
			timeAccumulator -= TICKRATIO;
			ticks++;
		}
	}
	return 0;
}