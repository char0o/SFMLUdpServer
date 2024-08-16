#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Globals.h"
#include "Entity.h"
#include "EntityList.h"
#include "GameState.h"
#include <iostream>
#include <string>
#include "NetManager.h"
#include "Packets.hpp"

using namespace std;
int main(int argc, char* argv[])
{
	cout << "Enter server IP: ";
	string ip;
	cin >> ip;
	cout << "Enter server port: ";
	unsigned short port;
	cin >> port;
	sf::UdpSocket* socket = CreateSocket(ip, port);
	if (socket == nullptr)
	{
		cout << "Failed to connect to server" << endl;
		system("pause");
		return 1;
	}

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML UDP Client");
	sf::Clock dtClock;
	float totalTime = 0.0f;
	window.setFramerateLimit(60);

	EntityList* currentEntityList = new EntityList();
	EntityList* nextEntityList = new EntityList();
	GameState* nextState = new GameState(nextEntityList);
	GameState* currentState = new GameState(currentEntityList);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{			
				window.close();
			}
		}
		Listen(*socket, currentState, nextState);

		sf::Time dt = dtClock.restart();
		totalTime += dt.asSeconds();
		window.clear();
		currentState->Color(sf::Color::Red);
		nextState->Color(sf::Color::Blue);
		currentState->Draw(window);
		nextState->Draw(window);
		window.display();
	}
	SendDisconnectPacket(*socket);
	if (socket != nullptr)
		delete socket;
	delete currentEntityList;
	delete nextEntityList;
	
}