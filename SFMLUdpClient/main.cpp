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
#include "Globals.h"
using namespace std;
int main(int argc, char* argv[])
{
	bool interp = true;
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
	sf::Clock clock;
	float accumulator = 0.0f;

	window.setFramerateLimit(165);

	EntityList* currentEntityList = new EntityList();
	EntityList* nextEntityList = new EntityList();
	GameState* nextState = new GameState(nextEntityList);
	GameState* currentState = new GameState(currentEntityList);
	while (window.isOpen())
	{
		sf::Event event;
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();
		accumulator += dt;
		while (accumulator >= TICKRATIO)
		{
			Listen(*socket, currentState, nextState);
			accumulator -= TICKRATIO;
		}
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{			
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::I)
				{
					
					interp = !interp;
					cout << "Interpolation: " << interp << endl;
				}
			}
		}
		
		
		window.clear();
		currentState->Draw(window);
		window.display();


		if (interp)
			InterPolateEntities(currentState, nextState, accumulator / TICKRATE);
	}
	SendDisconnectPacket(*socket);
	if (socket != nullptr)
		delete socket;
	delete currentEntityList;
	delete nextEntityList;
	
}