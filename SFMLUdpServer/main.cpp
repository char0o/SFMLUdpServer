#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "Packets.hpp"
#include "NetManager.h"
#include "Entity.h"
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

	Entity entity;
	while (!quit)
	{
		float dt = clock.restart().asSeconds();
		timeAccumulator += dt;
		totalTime += dt;

		while (timeAccumulator >= timeStep)
		{	
			Listen(socket);
			SendPlayerPos(socket, entity.GetPosition());
			entity.Update(sf::seconds(timeStep));
			timeAccumulator -= timeStep;
		}
	}
	return 0;
}