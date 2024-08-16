#pragma once
#include "SFML/Network.hpp"
#include "Packets.hpp"
#include <iostream>
void SendConnectPacket(sf::UdpSocket& socket);
void SendDisconnectPacket(sf::UdpSocket& socket);
void Listen(sf::UdpSocket& socket, EntityList& entityList);

const int CONNECTION_DELAY = 5;
sf::UdpSocket* CreateSocket(sf::IpAddress address, int port)
{
	std::cout << "Connecting to " << address << " on port " << port << std::endl;
	sf::UdpSocket* socket = new sf::UdpSocket();
	socket->setBlocking(false);
	if (socket->bind(CLIENT_PORT) != sf::Socket::Done)
	{
		std::cout << "Failed to bind socket" << std::endl;
	}
	sf::Clock clock;
	sf::Time lastChecked = sf::Time::Zero;
	while (clock.getElapsedTime().asSeconds() < CONNECTION_DELAY)
	{
		sf::Time elapsed = clock.getElapsedTime();
		if (elapsed.asSeconds() - lastChecked.asSeconds() >= 1)
		{
			std::cout << "Trying to connect..." << std::endl;;
			ConnectPacket connectPacket;
			socket->send(*connectPacket.GetPacket(), address, port);

			lastChecked = elapsed;

		}
		sf::Packet answer;
		sf::IpAddress sender;
		unsigned short senderPort;
		if (socket->receive(answer, sender, senderPort) == sf::Socket::Done)
		{
			int packetType;
			answer >> packetType;
			if (packetType == PacketType::Connect)
			{
				std::cout << "Connected to server" << std::endl;
				return socket;
			}
		}
	}
	delete socket;
	return nullptr;
}
void SendConnectPacket(sf::UdpSocket& socket)
{
	ConnectPacket connectPacket;
	socket.send(*connectPacket.GetPacket(), "localhost", 2000);
}

void SendDisconnectPacket(sf::UdpSocket& socket)
{
	DisconnectPacket disconnectPacket;
	socket.send(*disconnectPacket.GetPacket(), "localhost", 2000);
}

void Listen(sf::UdpSocket& socket, GameState*& currentState, GameState*& nextState)
{

	sf::Packet packet;
	sf::IpAddress sender;
	unsigned short port;
	sf::Vector2f position;
	if (socket.receive(packet, sender, port) != sf::Socket::Done)
	{
		return;
	}

	int packetType = 0;
	if (!(packet >> packetType))
	{
		std::cout << "No packet type" << std::endl;
	}
	switch (packetType)
	{
		int id;
	case PacketType::Entities:
	{
		GameState* tempCurrent = currentState;
		GameState* tempNext = nextState;
		currentState = tempNext;
		nextState = new GameState(tempCurrent->GetEntityList(), packet);
		delete tempCurrent;
	}
	break;
	case PacketType::Connect:
		packet >> id;
		std::cout << id;
		break;
	}
}
void InterPolateEntities(GameState* current, GameState* next, float alpha)
{
	if (current == nullptr || next == nullptr)
		return;
	EntityList* currentList = current->GetEntityList();
	EntityList* nextList = next->GetEntityList();
	if (currentList == nullptr || nextList == nullptr)
		return;
	for (int i = 0; i < currentList->GetSize(); i++)
	{
		BaseEntity* currentEntity = currentList->GetEntity(i);
		BaseEntity* nextEntity = nextList->GetEntityById(currentEntity->GetId());
		if (nextEntity == nullptr)
			continue;
		sf::Vector2f position = currentEntity->GetPosition() + (nextEntity->GetPosition() - currentEntity->GetPosition()) * alpha;
		currentEntity->SetPosition(position);
	}
}