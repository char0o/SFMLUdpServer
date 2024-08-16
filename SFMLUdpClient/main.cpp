#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "EntityList.h"
#include <iostream>
#include <string>
#include "NetManager.h"
#include "Packets.hpp"

using namespace std;
int main(int argc, char* argv[])
{
	sf::UdpSocket socket;
	socket.setBlocking(false);
	std::size_t received;
	sf::IpAddress sender;
	unsigned short port;
	if (socket.bind(2001) != sf::Socket::Done)
	{
		std::cout << "Error while binding the socket" << std::endl;
		return 0;
	}
	ConnectPacket connectPacket;
	if (socket.send(*connectPacket.GetPacket(), "localhost", 2000) != sf::Socket::Done)
	{
		std::cout << "Error while sending the message" << std::endl;
		return 0;
	}

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML UDP Client");
	sf::Clock dtClock;
	float totalTime = 0.0f;
	window.setFramerateLimit(60);


	EntityList entityList;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				SendDisconnectPacket(socket);
				window.close();
			}
		}
		Listen(socket, entityList);

		sf::Time dt = dtClock.restart();
		totalTime += dt.asSeconds();
		window.clear();
		entityList.Draw(window);
		window.display();
	}

}