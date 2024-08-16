#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "Globals.h"
#include "Client.h"
#include "ClientList.h"
#include "Packets.hpp"
#include "NetManager.h"
#include "Entity.h"
#include "EntityList.h"
#include <iostream>
#include <thread>
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
	Entity* entity = nullptr;
	for (int i = 1; i < 2; i++)
	{
		entity = new Entity();
		entity->SetId(i);
		Vector2f position(rand() % 800, rand() % 600); // Random position (0-800, 0-600
		Vector2f direction(rand() % 2 == 0 ? 1 : -1, rand() % 2 == 0 ? 1 : -1);
		entity->SetPosition(position);
		entity->SetDirection(direction);
		entityList.AddEntity(entity);
	}
	while (!quit)
	{
		float dt = clock.restart().asSeconds();
		timeAccumulator += dt;

		while (timeAccumulator >= TICKRATE)
		{	
			totalTime += sf::seconds(TICKRATE);
			Listen(socket, entityList, clientList);
			SendEntities(socket, entityList, clientList, ticks);
			entityList.Update(sf::seconds(TICKRATE));
			timeAccumulator -= TICKRATE;
			ticks++;
		}
	}
	return 0;
}