#include "SFML/Network.hpp"
#include "SFML/System.hpp"
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

	if (socket.bind(2000) != sf::Socket::Done)
	{
		std::cout << "Error while binding the socket" << std::endl;
		return -1;
	}
	const float timeStep = 1.0f / 60.0f;
	sf::Clock clock;
	float timeAccumulator = 0.0f;
	float totalTime = 0.0f;
	bool quit = false;


	EntityList entityList;
	Entity* entity = nullptr;
	for (int i = 1; i < 500; i++)
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
		totalTime += dt;

		while (timeAccumulator >= timeStep)
		{	
			Listen(socket, entityList);
			SendEntities(socket, entityList);
			entityList.Update(sf::seconds(timeStep));
			timeAccumulator -= timeStep;
		}
	}
	return 0;
}